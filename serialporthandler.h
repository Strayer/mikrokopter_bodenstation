#ifndef SERIALPORTHANDLER_H
#define SERIALPORTHANDLER_H

#include "qasyncserial/AsyncSerial.h"
#include "SerialPort.h"
#include "messages/basemessage.h"
class QByteArray;
class QMutex;
class QWaitCondition;
#include <QObject>
#include <QQueue>

class SerialPortHandler : public QObject
{
	Q_OBJECT

public:
	SerialPortHandler(SerialPort serialPort, QObject *parent = 0);
	~SerialPortHandler();

	QByteArray read(int length);
	void sendTestPing();

	void enqueueMessage(BaseMessage *msg);

public slots:
	void start();

private:
	void serialSlotReceivedData(const char *data, size_t size);

	CallbackAsyncSerial serial;
	SerialPort serialPort;

	QMutex *m_enqueueMessageMutex;
	QWaitCondition *m_waitCondition;
	QQueue<BaseMessage*> *m_messageQueue;
};

#endif // SERIALPORTHANDLER_H