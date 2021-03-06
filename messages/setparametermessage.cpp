#include "setparametermessage.h"
#include "helper_functions.h"
#include <QtCore>

SetParameterMessage::SetParameterMessage(uint16_t parameterTypeId, int32_t value)
	: m_parameterTypeId(parameterTypeId), m_value(value), BaseMessage(BaseMessage::MessageTypes::SET_PARAMETER)
{
}

QByteArray SetParameterMessage::prepareData()
{
	QByteArray tmp;

	tmp.append(intToQByteArray(m_parameterTypeId, 2));
	tmp.append(intToQByteArray((int64_t) m_value+2147483648, 4));

	return tmp;
}

QString SetParameterMessage::toString()
{
	return QString("SetParameterMessage (Parameter: %1, Value: %2)").arg(ParameterTypeIdToString(m_parameterTypeId)).arg(m_value);
}
