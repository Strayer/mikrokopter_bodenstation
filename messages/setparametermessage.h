#ifndef SETPARAMETERMESSAGE_H
#define SETPARAMETERMESSAGE_H

#include <stdint.h>
#include "basemessage.h"

class SetParameterMessage : public BaseMessage
{
public:
	SetParameterMessage(uint16_t parameterTypeId, int32_t value);

	QString toString();

private:
	uint16_t m_parameterTypeId;
	int32_t m_value;

private:
	QByteArray prepareData();
};

#endif // SETPARAMETERMESSAGE_H
