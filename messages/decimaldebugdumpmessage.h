#ifndef DECIMALDEBUGDUMPMESSAGE_H
#define DECIMALDEBUGDUMPMESSAGE_H

#include <stdint.h>
#include "basemessage.h"

class DecimalDebugDumpMessage : public BaseMessage
{
public:
	DecimalDebugDumpMessage();

	const QList<uint8_t>* decimals();
	void addDecimal(uint8_t decimal);

	QString toString();

	static DecimalDebugDumpMessage* fromRawData(QByteArray rawData);

private:
	QList<uint8_t> *m_decimals;
};

#endif // DECIMALDEBUGDUMPMESSAGE_H
