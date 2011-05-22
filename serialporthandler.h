#ifndef SERIALPORTHANDLER_H
#define SERIALPORTHANDLER_H

#include "qasyncserial/QAsyncSerial.h"
#include "SerialPort.h"
class QByteArray;
#include <QObject>

class SerialPortHandler : QObject
{
	Q_OBJECT

public:
	SerialPortHandler(SerialPort serialPort, QObject *parent = 0);

	QByteArray read(int length);
	void sendTestPing();

private slots:
	void serialSlotReceivedData(QByteArray line);

private:
	QAsyncSerial serial;
	SerialPort serialPort;
};

#endif // SERIALPORTHANDLER_H
