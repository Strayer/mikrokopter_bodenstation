#include "serialportdevice.h"

SerialPortDevice::SerialPortDevice(const char* serialDeviceName) : io(), serial(io, serialDeviceName)
{
}
