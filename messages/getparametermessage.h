#ifndef GETPARAMETERMESSAGE_H
#define GETPARAMETERMESSAGE_H

#include <stdint.h>
#include "basemessage.h"

class GetParameterMessage : public BaseMessage
{
public:
	GetParameterMessage(uint16_t parameterTypeId);

	QString toString();

private:
	uint16_t m_parameterTypeId;

private:
	QByteArray prepareData();
};

#endif // GETPARAMETERMESSAGE_H
