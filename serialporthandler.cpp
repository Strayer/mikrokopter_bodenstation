#include "serialporthandler.h"

#include "messages/pingmessage.h"

#include <QtDebug>

SerialPortHandler::SerialPortHandler(SerialPort serialPort, QObject *parent) : QObject(parent), serialPort(serialPort)
{
	serial.open(serialPort.deviceName(), 2400);
	connect(&serial, SIGNAL(dataReceived(QByteArray)), this, SLOT(serialSlotReceivedData(QByteArray)));
}

void SerialPortHandler::serialSlotReceivedData(QByteArray line)
{
	qDebug() << QString(line).toAscii();
}

void SerialPortHandler::sendTestPing()
{
	PingMessage msg;

	serial.write(msg.encodeForWriting());
}
