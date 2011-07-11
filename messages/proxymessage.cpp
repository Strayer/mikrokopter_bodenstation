#include "proxymessage.h"
#include "helper_functions.h"

ProxyMessage::ProxyMessage()
{
}

void ProxyMessage::setInnerMessage(QSharedPointer<BaseMessage> msg)
{
	m_innerMessage = msg;
}

QByteArray ProxyMessage::prepareData()
{
	QByteArray type = intToQByteArray(m_innerMessage->messageType(), 3);
	QByteArray data = m_innerMessage->prepareData();
	QByteArray innerData = QByteArray().append(type).append(data);

	return intToQByteArray(innerData.size(), 2).append(innerData);
}

QString ProxyMessage::toString()
{
	return QString("ProxyMessage: %1").arg(m_innerMessage->toString());
}
