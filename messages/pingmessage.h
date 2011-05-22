#ifndef PINGMESSAGE_H
#define PINGMESSAGE_H

#include "basemessage.h"

class PingMessage : public BaseMessage
{
public:
    PingMessage();

	int sequenceNumber();

protected:
	int _sequenceNumber;

private:
	QByteArray prepareData();
};

#endif // PINGMESSAGE_H
