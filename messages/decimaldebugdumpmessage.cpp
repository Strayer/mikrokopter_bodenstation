#include "decimaldebugdumpmessage.h"
#include "helper_functions.h"

DecimalDebugDumpMessage::DecimalDebugDumpMessage() : BaseMessage(BaseMessage::MessageTypes::DECIMAL_DEBUG_DUMP)
{
	m_decimals = new QList<uint8_t>();
}

DecimalDebugDumpMessage* DecimalDebugDumpMessage::fromRawData(QByteArray data)
{
	DecimalDebugDumpMessage *tmp = new DecimalDebugDumpMessage();

	for (int i = 0; i < data.size(); i++)
		tmp->addDecimal((int8_t) QByteArrayToInt(data.mid(i, 1)));

	return tmp;
}

void DecimalDebugDumpMessage::addDecimal(uint8_t decimal)
{
	m_decimals->append(decimal);
}

const QList<uint8_t>* DecimalDebugDumpMessage::decimals()
{
	return m_decimals;
}

QString DecimalDebugDumpMessage::toString()
{
	QString numbers;

	for (int i = 0; i < m_decimals->size(); i++)
		numbers.append(QString::number(m_decimals->at(i))).append(", ");
	numbers = numbers.left(numbers.length() - 2);

	return QString("DecimalDebugDumpMessage ([%1])").arg(numbers);
}
