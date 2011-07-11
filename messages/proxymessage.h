#ifndef PROXYMESSAGE_H
#define PROXYMESSAGE_H

#include "basemessage.h"
#include <QSharedPointer>

class ProxyMessage : public BaseMessage
{
public:
    ProxyMessage();

	void setInnerMessage(QSharedPointer<BaseMessage> msg);
	QString toString();

private:
	QSharedPointer<BaseMessage> m_innerMessage;

	QByteArray prepareData();
};

#endif // PROXYMESSAGE_H
