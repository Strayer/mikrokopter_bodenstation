#include "pongmessage.h"

#include "helper_functions.h"

#include <QString>

PongMessage::PongMessage() : BaseMessage(BaseMessage::MessageTypes::PONG)
{
}

PongMessage* PongMessage::fromRawData(QByteArray data)
{
	PongMessage *tmp = new PongMessage();
	tmp->_sequenceNumber = QByteArrayToInt(data);

	return tmp;
}

QString PongMessage::toString()
{
	return QString("PongMessage (sequenceNumber: %1)").arg(_sequenceNumber);
}
