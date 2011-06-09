#include "serialporthandler.h"
#include "messages/all_messages.h"

#include <QtDebug>
#include <QtCore>

SerialPortHandler::SerialPortHandler(SerialPort serialPort, QObject *parent) : QObject(parent), serialPort(serialPort)
{
	m_enqueueMessageMutex = new QMutex();
	m_messageQueue = new QQueue< QSharedPointer<BaseMessage> >();
	m_waitCondition = new QWaitCondition();
	serial.open(QString(serialPort.deviceName()).toStdString(), 2400);
	serial.setCallback(bind(&SerialPortHandler::serialSlotReceivedData, this, _1, _2));

	m_messageProcessingState = MessageProcessingState::Inactive;
}

SerialPortHandler::~SerialPortHandler()
{
	delete m_enqueueMessageMutex;
	delete m_waitCondition;
	delete m_messageQueue;
}

void SerialPortHandler::serialSlotReceivedData(const char *data, size_t size)
{
	for (int i = 0; i < size; i++)
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
			emit newMessageReceived(pointer);
		}
	}
}

void SerialPortHandler::sendTestPing()
{
	auto msg = QSharedPointer<BaseMessage>(new PingMessage());
	enqueueMessage(msg);
}

void SerialPortHandler::enqueueMessage(QSharedPointer<BaseMessage> msg)
{
	QMutexLocker locker(m_enqueueMessageMutex);
	qDebug() << "Fuege Nachricht" << QString::number(msg->messageType()).toAscii().toHex() << "zum Queue hinzu";
	m_messageQueue->enqueue(msg);
	m_waitCondition->wakeAll();
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
			m_waitCondition->wait(m_enqueueMessageMutex);
			qDebug() << "waitCondition gefeuert";
		}
		QSharedPointer<BaseMessage> msg = m_messageQueue->dequeue();
		qDebug() << "Sende Nachricht" << QString::number(msg->messageType()).toAscii().toHex();
		QByteArray encodedMessage = msg->encodeForWriting();
		serial.write(encodedMessage.constData(), encodedMessage.length());
		emit messageSent(msg);
		m_enqueueMessageMutex->unlock();
	}
}
