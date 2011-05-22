#ifndef SERIALPORTHANDLER_H
#define SERIALPORTHANDLER_H

#include "qasyncserial/QAsyncSerial.h"

class QByteArray;
#include <QObject>

class SerialPortHandler : QObject
{
	Q_OBJECT

public:
	SerialPortHandler(QString serialDeviceName, QObject *parent = 0);

	QByteArray read(int length);
	void sendTestPing();

private slots:
	void serialSlotReceivedData(QByteArray line);

private:
	QAsyncSerial serial;
};

#endif // SERIALPORTHANDLER_H
