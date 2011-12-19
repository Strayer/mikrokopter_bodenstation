#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QString>
#include <QMetaType>
#include <QDebug>

class SerialPort {
public:
	SerialPort() { _portNum = 0; }
	SerialPort(uint portNum, QString friendlyName) : _portNum(portNum), _friendlyName(friendlyName) {}
	SerialPort(uint portNum, std::wstring friendlyName) : _portNum(portNum) { _friendlyName = QString::fromStdWString(friendlyName); }

	void setPortNum(uint num) { _portNum = num; }
	uint portNum() const { return _portNum; }

	void setFriendlyName(QString name) { _friendlyName = name; }
	QString friendlyName() const { return _friendlyName; }

	QByteArray deviceName() { return QString("COM%1").arg(_portNum).toAscii(); }

private:
	uint _portNum;
	QString _friendlyName;
};

Q_DECLARE_METATYPE(SerialPort);

QDebug operator<<(QDebug dbg, const SerialPort &port);

#endif // SERIALPORT_H
