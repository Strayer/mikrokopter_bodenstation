#ifndef BASEMESSAGE_H
#define BASEMESSAGE_H

#define ESC (char) 0x1B
#define STX (char) 0x01
#define ETB (char) 0x17

#include <QByteArray>
#include <QMetaType>

class BaseMessage
{
public:
	BaseMessage(int type);
	BaseMessage();

	bool isNull();

	int messageType();

	QByteArray encodeForWriting();

	class MessageTypes {
	public:
		enum {
			NOP = 0x000000,
			ACK = 0x000001,
			PROXY_MESSAGE = 0x000002,
			SET_PARAMETER = 0x000003,
			CUR_PARAMETER = 0x000004,
			GET_PARAMETER = 0x000005,
			PING = 0x000006,
			PONG = 0x000007,
			SET_LEDS = 0x000008,
			CLEAR_TO_SEND = 0x000009,
			BUFFER_REPORT = 0x00000a,
			OUT_BUFFER_FULL = 0x00000b,
			DO_ACCEL_CALIBRATION = 0x00000c,
			ACCEL_CALIBRATION_DONE = 0x00000d,
			DO_GYRO_CALIBRATION = 0x00000e,
			GYRO_CALIBRATION_DONE = 0x00000f
		};
	};

	static BaseMessage* fromRawData(QByteArray rawData);

	virtual void setData();
	virtual QString toString();
	virtual QByteArray prepareData();

private:
	int m_messageType;
	bool m_isNull;

	QByteArray typeIntToBytes();

	static QByteArray escapeByteArray(QByteArray data);
	static QByteArray generateCRC8(QByteArray data);
};

#endif // BASEMESSAGE_H
