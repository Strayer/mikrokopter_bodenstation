#include "cleartosendmessage.h"

#include "helper_functions.h"
#include <QString>

ClearToSendMessage::ClearToSendMessage() : BaseMessage(BaseMessage::MessageTypes::CLEAR_TO_SEND)
{
}

QString ClearToSendMessage::toString()
{
	return QString("ClearToSendMessage");
}
