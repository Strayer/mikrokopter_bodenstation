#include "proxymessage.h"

ProxyMessage::ProxyMessage()
{
}

void ProxyMessage::setInnerData(int messageType, QByteArray data)
{
	m_innerMessageType = messageType;
	m_innerData = data;
}

QByteArray ProxyMessage::prepareData()
{
	return m_innerData;
}

QString ProxyMessage::toString()
{
	return QString("ProxyMessage");
}
