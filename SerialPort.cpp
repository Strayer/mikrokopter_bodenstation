#include "SerialPort.h"

QDebug operator<<(QDebug dbg, const SerialPort &port)
{
    dbg.nospace() << "SerialPort(" << port.portNum() << ", " << port.friendlyName() << ")";
    return dbg.maybeSpace();
}
