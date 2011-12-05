#ifndef CURPARAMETERMESSAGE_H
#define CURPARAMETERMESSAGE_H

#include <stdint.h>
#include "basemessage.h"

class CurParameterMessage : public BaseMessage
{
public:
	CurParameterMessage();

	uint16_t parameterTypeId();
	int32_t value();
	QString toString();

	void setParameterTypeId(uint16_t parameterTypeId) { m_parameterTypeId = parameterTypeId; }
	void setValue(int32_t value) { m_value = value; }

	static CurParameterMessage* fromRawData(QByteArray data);

private:
	uint16_t m_parameterTypeId;
	int32_t m_value;
	uint16_t _sequenceNumber;
};

#endif // CURPARAMETERMESSAGE_H
