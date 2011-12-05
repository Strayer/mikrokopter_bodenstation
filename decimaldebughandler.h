#ifndef DECIMALDEBUGHANDLER_H
#define DECIMALDEBUGHANDLER_H

#include "messages/all_messages.h"

#include <QObject>
#include <QFile>

class DecimalDebugHandler : public QObject
{
	Q_OBJECT

public:
	DecimalDebugHandler();

public slots:
	void start();
	void newMessageReceived(QSharedPointer<BaseMessage> msg);

private:
	QFile m_debugFile;
};

#endif // DECIMALDEBUGHANDLER_H
