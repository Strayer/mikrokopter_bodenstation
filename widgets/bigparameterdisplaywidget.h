#ifndef BIGPARAMETERDISPLAYWIDGET_H
#define BIGPARAMETERDISPLAYWIDGET_H

#include <QWidget>

#include <messages/all_messages.h>
#include <serialporthandler.h>

class QLabel;
class QVBoxLayout;

class BigParameterDisplayWidget : public QWidget
{
	Q_OBJECT
public:
	explicit BigParameterDisplayWidget(SerialPortHandler *handler, QWidget *parent = 0);
	~BigParameterDisplayWidget();

private:
	QHash<int, QLabel*> m_typeIdToLabelHash;
	QVBoxLayout *m_layout;

public slots:
	void newMessageReceived(QSharedPointer<BaseMessage> msg);
	void showSetupWindow();

	void fitLabelsToContent();

protected:
	void resizeEvent(QResizeEvent *event);
};

#endif // BIGPARAMETERDISPLAYWIDGET_H
