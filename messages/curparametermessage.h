#ifndef CURPARAMETERMESSAGE_H
#define CURPARAMETERMESSAGE_H

#include <stdint.h>
#include "basemessage.h"

class CurParameterMessage : public BaseMessage
{
public:
	CurParameterMessage();

	uint16_t parameterTypeId();
	uint32_t value();
	QString toString();

	void setParameterTypeId(uint16_t parameterTypeId) { m_parameterTypeId = parameterTypeId; }
	void setValue(uint32_t value) { m_value = value; }

	static CurParameterMessage* fromRawData(QByteArray data);

private:
	uint16_t m_parameterTypeId;
	uint32_t m_value;

private:
	uint16_t _sequenceNumber;
};

#endif // CURPARAMETERMESSAGE_H
