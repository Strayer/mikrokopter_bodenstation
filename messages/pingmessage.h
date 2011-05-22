#ifndef PINGMESSAGE_H
#define PINGMESSAGE_H

#include <stdint.h>
#include "basemessage.h"

class PingMessage : public BaseMessage
{
public:
    PingMessage();

	uint16_t sequenceNumber();

protected:
	uint16_t _sequenceNumber;

private:
	QByteArray prepareData();
};

#endif // PINGMESSAGE_H
