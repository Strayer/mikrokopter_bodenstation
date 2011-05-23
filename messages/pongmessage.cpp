#include "pongmessage.h"

#include "helper_functions.h"

PongMessage::PongMessage() : BaseMessage(BaseMessage::MessageTypes::PONG)
{
}

PongMessage PongMessage::fromRawData(QByteArray data)
{
	PongMessage tmp;
	tmp._sequenceNumber = QByteArrayToInt(data);

	return tmp;
}
