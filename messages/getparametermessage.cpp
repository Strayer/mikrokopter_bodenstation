#include "getparametermessage.h"
#include "helper_functions.h"
#include <QtCore>

GetParameterMessage::GetParameterMessage(uint16_t parameterTypeId)
	: m_parameterTypeId(parameterTypeId), BaseMessage(BaseMessage::MessageTypes::GET_PARAMETER)
{
}

QByteArray GetParameterMessage::prepareData()
{
	return intToQByteArray(m_parameterTypeId, 2);
}

QString GetParameterMessage::toString()
{
	return QString("GetParameterMessage (Parameter: %1)").arg(ParameterTypeIdToString(m_parameterTypeId));
}
