#ifndef PONGMESSAGE_H
#define PONGMESSAGE_H

#include <stdint.h>
#include "basemessage.h"

class PongMessage : public BaseMessage
{
public:
    PongMessage();

	uint16_t sequenceNumber();

	static PongMessage fromRawData(QByteArray data);

private:
	uint16_t _sequenceNumber;
};

#endif // PONGMESSAGE_H
