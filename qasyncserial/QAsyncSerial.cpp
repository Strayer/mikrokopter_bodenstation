/**
 * Author: Terraneo Federico
 * Distributed under the Boost Software License, Version 1.0.
 */

#include "QAsyncSerial.h"
#include "AsyncSerial.h"
#include <QStringList>
#include <QRegExp>

/**
 * Implementation details of QAsyncSerial class.
 */
class QAsyncSerialImpl
{
public:
    CallbackAsyncSerial serial;
    QString receivedData;
};

QAsyncSerial::QAsyncSerial(): pimpl(new QAsyncSerialImpl)
{
}

QAsyncSerial::QAsyncSerial(QString devname, unsigned int baudrate)
        : pimpl(new QAsyncSerialImpl)
{
	open(devname,baudrate);
}

void QAsyncSerial::open(QString devname, unsigned int baudrate)
{
    try {
        pimpl->serial.open(devname.toStdString(),baudrate);
    } catch(boost::system::system_error&)
    {
        //Errors during open
    }
    pimpl->serial.setCallback(bind(&QAsyncSerial::readCallback,this, _1, _2));
}

void QAsyncSerial::close()
{
    pimpl->serial.clearCallback();
    try {
        pimpl->serial.close();
    } catch(boost::system::system_error&)
    {
        //Errors during port close
    }
    pimpl->receivedData.clear();//Clear eventual data remaining in read buffer
}

bool QAsyncSerial::isOpen()
{
    return pimpl->serial.isOpen();
}

bool QAsyncSerial::errorStatus()
{
    return pimpl->serial.errorStatus();
}

void QAsyncSerial::write(QString data)
{
    pimpl->serial.writeString(data.toStdString());
}

void QAsyncSerial::write(QByteArray data)
{
	pimpl->serial.write(data.constData(), data.length());
}

QAsyncSerial::~QAsyncSerial()
{
    pimpl->serial.clearCallback();
    try {
        pimpl->serial.close();
    } catch(...)
    {
        //Don't throw from a destructor
    }
}

void QAsyncSerial::readCallback(const char *data, size_t size)
{
	emit dataReceived(QByteArray::fromRawData(data, (int) size));
}
