#include "basemessage.h"
#include "boost/crc.hpp"

#include "all_messages.h"
#include "helper_functions.h"

#include <QtDebug>

BaseMessage::BaseMessage(int type) : m_messageType(type)
{
	m_isNull = false;
}

BaseMessage::BaseMessage() : m_messageType(0)
{
	m_isNull = true;
}

int BaseMessage::messageType()
{
	return m_messageType;
}

bool BaseMessage::isNull()
{
	return m_isNull;
}

QByteArray BaseMessage::typeIntToBytes()
{
	return QByteArray();
}

QByteArray BaseMessage::encodeForWriting()
{
	QByteArray type = intToQByteArray(messageType(), 3);
	QByteArray data = prepareData();
	QByteArray crc8 = BaseMessage::generateCRC8(QByteArray().append(type).append(data));

	qDebug() << "Type:" << type.toHex();
	qDebug() << "Data:" << data.toHex();
	qDebug() << "CRC8:" << crc8.toHex();

	QByteArray tmp;
	tmp.append(STX);
	tmp.append(STX);
	tmp.append(BaseMessage::escapeByteArray(type));
	tmp.append(BaseMessage::escapeByteArray(data));
	tmp.append(BaseMessage::escapeByteArray(crc8));
	tmp.append(ETB);

	return tmp;
}

BaseMessage* BaseMessage::fromRawData(QByteArray rawData)
{
	QByteArray crc8 = rawData.right(1);
	QByteArray dataCRC8 = BaseMessage::generateCRC8(rawData.left(rawData.size()-1));

	if (crc8 != dataCRC8)
	{
		qDebug() << "Kaputte Nachricht:" << rawData.toHex();
		return new BaseMessage();
	}

	int type = QByteArrayToInt(rawData.left(3));
	QByteArray data = rawData.mid(3, rawData.length()-4);

	BaseMessage *msg = new BaseMessage();

	switch (type)
	{
	case MessageTypes::PONG:
		msg = PongMessage::fromRawData(data);
		break;
	case MessageTypes::PING:
		qDebug() << "BaseMessage::fromRawData: Nachricht PING kann nur gesendet werden";
	default:
		qDebug() << "BaseMessage::fromRawData: Unbekannte Nachricht" << QByteArray().append(type).toHex();
	}

	return msg;
}

QByteArray BaseMessage::escapeByteArray(QByteArray data)
{
	return data
			.replace(ESC, QByteArray().append(ESC).append(ESC))
			.replace(STX, QByteArray().append(ESC).append(STX))
			.replace(ETB, QByteArray().append(ESC).append(ETB));
}

QByteArray BaseMessage::generateCRC8(QByteArray data)
{
	boost::crc_basic<8> crc8(0x07);

	crc8.process_bytes(data.constData(), data.length());

	return QByteArray(1, crc8.checksum());
}

QByteArray BaseMessage::prepareData()
{
	return QByteArray();
}

void BaseMessage::setData()
{
	return;
}

QString BaseMessage::toString()
{
	return QString("BaseMessage");
}
