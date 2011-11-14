#include "curparametermessage.h"
#include "helper_functions.h"
#include <QString>

CurParameterMessage::CurParameterMessage() : BaseMessage(BaseMessage::MessageTypes::CUR_PARAMETER)
{
}

CurParameterMessage* CurParameterMessage::fromRawData(QByteArray data)
{
	CurParameterMessage *tmp = new CurParameterMessage();
	tmp->setParameterTypeId(QByteArrayToInt(data.left(2)));
	tmp->setValue((int64_t) QByteArrayToInt(data.right(4))-2147483648);

	return tmp;
}

uint16_t CurParameterMessage::parameterTypeId()
{
	return m_parameterTypeId;
}

int32_t CurParameterMessage::value()
{
	return m_value;
}

QString CurParameterMessage::toString()
{
	return QString("CurParameterMessage (Parameter: %1, Value: %2)").arg(ParameterTypeIdToString(m_parameterTypeId)).arg(m_value);
}
