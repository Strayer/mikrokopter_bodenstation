#include "pingmessage.h"
#include "helper_functions.h"
#include <QtCore>

PingMessage::PingMessage() : BaseMessage(BaseMessage::MessageTypes::PING)
{
	static uint16_t seq_number = 0;

	_sequenceNumber = ++seq_number;
}

QByteArray PingMessage::prepareData()
{
	return intToQByteArray(_sequenceNumber, 2);
}
