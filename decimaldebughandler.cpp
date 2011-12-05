#include "decimaldebughandler.h"

#include <QCoreApplication>

DecimalDebugHandler::DecimalDebugHandler() : QObject()
{
	m_debugFile.setFileName(QCoreApplication::instance()->applicationDirPath().append("/decimal_debug.txt"));
	m_debugFile.open(QFile::Append);
}

void DecimalDebugHandler::start()
{
}

void DecimalDebugHandler::newMessageReceived(QSharedPointer<BaseMessage> msg)
{
	if (!m_debugFile.isOpen())
		return;

	if (msg->messageType() == BaseMessage::MessageTypes::DECIMAL_DEBUG_DUMP)
	{
		QSharedPointer<DecimalDebugDumpMessage> decimalMsg = msg.staticCast<DecimalDebugDumpMessage>();

		const QList<uint8_t> *decimals = decimalMsg->decimals();
		for (int i = 0; i < decimals->size(); i++)
		{
			m_debugFile.write(QString::number(decimals->at(i)).toAscii());
			m_debugFile.write("\n");
		}
		m_debugFile.flush();
	}
}
