#include "serialporthandler.h"

#include "messages/pingmessage.h"

#include <QtDebug>

SerialPortHandler::SerialPortHandler(QString serialDeviceName, QObject *parent) : QObject(parent)
{
	connect(&serial, SIGNAL(dataReceived(QByteArray)), this, SLOT(serialSlotReceivedData(QByteArray)));
	serial.open(serialDeviceName, 2400);
}

void SerialPortHandler::serialSlotReceivedData(QByteArray line)
{
	qDebug() << line;
}

void SerialPortHandler::sendTestPing()
{
	PingMessage msg;

	qDebug() << msg.encodeForWriting();

	serial.write(msg.encodeForWriting());
}
