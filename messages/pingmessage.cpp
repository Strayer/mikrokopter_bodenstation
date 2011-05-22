#include "pingmessage.h"

#include <QtCore>

PingMessage::PingMessage() : BaseMessage(BaseMessage::MessageTypes::PING)
{
	static int seq_number = 0;

	_sequenceNumber = ++seq_number;
}

QByteArray PingMessage::prepareData()
{
	return QString::number(_sequenceNumber).toAscii();
}
