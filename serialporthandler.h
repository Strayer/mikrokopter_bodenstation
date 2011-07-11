#ifndef SERIALPORTHANDLER_H
#define SERIALPORTHANDLER_H

#include "AsyncSerial.h"
#include "SerialPort.h"
#include "messages/basemessage.h"
class QByteArray;
class QMutex;
class QWaitCondition;
#include <QObject>
#include <QQueue>
#include <QSharedPointer>

class SerialPortHandler : public QObject
{
	Q_OBJECT

public:
	SerialPortHandler(SerialPort serialPort, QObject *parent = 0);
	~SerialPortHandler();

	QByteArray read(int length);

	void enqueueMessage(QSharedPointer<BaseMessage> msg);

public slots:
	void start();

signals:
	void newMessageReceived(QSharedPointer<BaseMessage>);
	void messageSent(QSharedPointer<BaseMessage>);

private:
	void serialSlotReceivedData(const char *data, size_t size);

	CallbackAsyncSerial serial;
	SerialPort serialPort;

	QMutex *m_enqueueMessageMutex;
	QWaitCondition *m_waitCondition;
	QQueue< QSharedPointer<BaseMessage> > *m_messageQueue;

	int m_messageProcessingState;
	QByteArray m_messageProcessingBuffer;
	class MessageProcessingState {
	public:
		enum { Inactive, InMessage, AfterMessage, AfterEscape };
	};
};

#endif // SERIALPORTHANDLER_H
