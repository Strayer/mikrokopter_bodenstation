#include "serialporthandler.h"
#include "messages/all_messages.h"

#include <QtDebug>
#include <QtCore>

SerialPortHandler::SerialPortHandler(SerialPort serialPort, QObject *parent) : QObject(parent), serialPort(serialPort)
{
	m_enqueueMessageMutex = new QMutex();
	m_messageQueue = new QQueue<BaseMessage*>();
	m_waitCondition = new QWaitCondition();
	serial.open(QString(serialPort.deviceName()).toStdString(), 2400);
	serial.setCallback(bind(&SerialPortHandler::serialSlotReceivedData, this, _1, _2));
}

SerialPortHandler::~SerialPortHandler()
{
	delete m_enqueueMessageMutex;
	delete m_waitCondition;
	delete m_messageQueue;
}

void SerialPortHandler::serialSlotReceivedData(const char *data, size_t size)
{
	QByteArray line = QByteArray::fromRawData(data, (int) size);
	qDebug() << QString(line).toAscii();
}

void SerialPortHandler::sendTestPing()
{
	PingMessage *msg = new PingMessage();
	enqueueMessage(msg);
}

void SerialPortHandler::enqueueMessage(BaseMessage *msg)
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
		while (m_messageQueue->isEmpty())
		{
			qDebug() << "Keine Nachrichten mehr im Queue... warte auf neue Nachrichten";
			if (m_waitCondition->wait(m_enqueueMessageMutex))
				qDebug() << "waitCondition gefeuert";
			else
				qDebug() << "waitCondition timeout";
			QCoreApplication::processEvents();
		}
		BaseMessage *msg = m_messageQueue->dequeue();
		qDebug() << "Sende Nachricht" << QString::number(msg->messageType()).toAscii().toHex();
		QByteArray encodedMessage = msg->encodeForWriting();
		serial.write(encodedMessage.constData(), encodedMessage.length());
		delete msg;
		m_enqueueMessageMutex->unlock();
	}
}
