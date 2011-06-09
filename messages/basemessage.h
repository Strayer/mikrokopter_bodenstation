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
			PROXY_MESSAGE = 0x000000,
			SET_PARAMETER = 0x000001,
			CUR_PARAMETER = 0x000002,
			GET_PARAMETER = 0x000003,
			PING = 0x000004,
			PONG = 0x000005
		};
	};

	static BaseMessage* fromRawData(QByteArray rawData);

	virtual void setData();
	virtual QString toString();

protected:
	virtual QByteArray prepareData();

private:
	int m_messageType;
	bool m_isNull;

	QByteArray typeIntToBytes();

	static QByteArray escapeByteArray(QByteArray data);
	static QByteArray generateCRC8(QByteArray data);
};

#endif // BASEMESSAGE_H
