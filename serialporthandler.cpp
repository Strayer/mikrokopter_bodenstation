#include "serialporthandler.h"
#include "messages/all_messages.h"

#include <QtDebug>
#include <QtCore>

SerialPortHandler::SerialPortHandler(SerialPort serialPort, QObject *parent) : QObject(parent), serialPort(serialPort)
{
	m_enqueueMessageMutex = new QMutex();
	m_resetSendBufferMutex = new QMutex();
	m_messageQueue = new QQueue< QSharedPointer<BaseMessage> >();
	m_emptyQueueWaitCondition = new QWaitCondition();
	m_fullBufferWaitCondition = new QWaitCondition();
	serial.open(QString(serialPort.deviceName()).toStdString(), 57600);
	serial.setCallback(bind(&SerialPortHandler::serialSlotReceivedData, this, _1, _2));

	m_remainingSendBuffer = MAX_SERIAL_SEND_BUFFER;

	m_messageProcessingState = MessageProcessingState::Inactive;
}

SerialPortHandler::~SerialPortHandler()
{
	delete m_enqueueMessageMutex;
	delete m_emptyQueueWaitCondition;
	delete m_messageQueue;
}

void SerialPortHandler::serialSlotReceivedData(const char *data, size_t size)
{
	for (uint i = 0; i < size; i++)
	{
		char currChar = data[i];

		if (m_messageProcessingState != MessageProcessingState::AfterEscape && currChar == STX)
		{
			m_messageProcessingBuffer.clear();
			m_messageProcessingState = MessageProcessingState::InMessage;
		}
		else if (m_messageProcessingState == MessageProcessingState::InMessage && currChar == ESC)
			m_messageProcessingState = MessageProcessingState::AfterEscape;
		else if (m_messageProcessingState == MessageProcessingState::InMessage && currChar == ETB)
			m_messageProcessingState = MessageProcessingState::AfterMessage;
		else if (m_messageProcessingState == MessageProcessingState::AfterEscape || m_messageProcessingState == MessageProcessingState::InMessage)
		{
			m_messageProcessingBuffer.append(currChar);

			if (m_messageProcessingState == MessageProcessingState::AfterEscape)
				m_messageProcessingState = MessageProcessingState::InMessage;
		}

		if (m_messageProcessingState == MessageProcessingState::AfterMessage)
		{
			auto pointer = QSharedPointer<BaseMessage>(BaseMessage::fromRawData(m_messageProcessingBuffer));

			if (pointer->messageType() == BaseMessage::MessageTypes::CLEAR_TO_SEND)
			{
				m_resetSendBufferMutex->lock();
				m_remainingSendBuffer = MAX_SERIAL_SEND_BUFFER;
				m_resetSendBufferMutex->unlock();
				m_fullBufferWaitCondition->wakeAll();
			}
			else
				emit newMessageReceived(pointer);
		}
	}
}

void SerialPortHandler::enqueueMessage(QSharedPointer<BaseMessage> msg)
{
	QMutexLocker locker(m_enqueueMessageMutex);
	qDebug() << "Nachricht an den Sendequeue angehaengt:" << msg->toString();
	m_messageQueue->enqueue(msg);
	m_emptyQueueWaitCondition->wakeAll();
}

void SerialPortHandler::start()
{
	if (!serial.isOpen())
		return;

	forever {
		m_enqueueMessageMutex->lock();
		if (m_messageQueue->isEmpty())
		{
			qDebug() << "Keine Nachrichten mehr im Queue... warte auf neue Nachrichten";
			m_emptyQueueWaitCondition->wait(m_enqueueMessageMutex);
		}
		QSharedPointer<BaseMessage> msg = m_messageQueue->dequeue();
		m_enqueueMessageMutex->unlock();

		qDebug() << "Sende Nachricht" << msg->toString();

		QByteArray encodedMessage = msg->encodeForWriting();

		m_resetSendBufferMutex->lock();

		if (encodedMessage.size() > m_remainingSendBuffer)
		{
			qDebug() << "Nachrichtensendepuffer voll... warte auf CLEAR_TO_SEND";
			// Solange der Puffer nicht wieder freigegeben wurde wird jede Sekunde Müll geschickt um ein CLEAR_TO_SEND anzuregen
			while(m_remainingSendBuffer < encodedMessage.size() && !m_fullBufferWaitCondition->wait(m_resetSendBufferMutex, 1000))
				serial.write(QByteArray(1, ETB).constData(), 1);
			qDebug() << "CLEAR_TO_SEND, Nachrichtensendepuffer zurückgesetzt";
		}

		m_remainingSendBuffer-= encodedMessage.size();
		serial.write(encodedMessage.constData(), encodedMessage.size());

		m_resetSendBufferMutex->unlock();

		emit messageSent(msg);
	}
}
