#ifndef SERIALPORTDEVICE_H
#define SERIALPORTDEVICE_H

#include <boost/system/system_error.hpp>
#include <boost/asio.hpp>

class SerialPortDevice
{
public:
	SerialPortDevice(const char* serialDeviceName);

private:
	boost::asio::io_service io;
	boost::asio::serial_port serial;
};

#endif // SERIALPORTDEVICE_H
