#ifndef CLEARTOSENDMESSAGE_H
#define CLEARTOSENDMESSAGE_H

#include "basemessage.h"

class ClearToSendMessage : public BaseMessage
{
public:
	ClearToSendMessage();

	QString toString();
};

#endif // CLEARTOSENDMESSAGE_H
