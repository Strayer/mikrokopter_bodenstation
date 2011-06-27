#ifndef PROXYMESSAGE_H
#define PROXYMESSAGE_H

#include "basemessage.h"

class ProxyMessage : public BaseMessage
{
public:
    ProxyMessage();

	void setInnerData(int messageType, QByteArray data);
	QString toString();

private:
	int m_innerMessageType;
	QByteArray m_innerData;

	QByteArray prepareData();
};

#endif // PROXYMESSAGE_H
