#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QSettings>

#include "messages/all_messages.h"

class SerialPortHandler;
class QListWidget;
class ParametersWidget;

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	explicit MainWindow(QWidget *parent = 0);

	void enqueueMessage(QSharedPointer<BaseMessage> msg);

	void keyReleaseEvent(QKeyEvent *event);

private:
	SerialPortHandler *serial;
	QThread serialPortThread;

	QSettings settings;

	QListWidget *msgList;
	ParametersWidget *parametersWidget;

	void closeEvent(QCloseEvent *event);

signals:

public slots:
	void sendPingButtonClicked();
	void sendProxyPingButtonClicked();

	void newMessageReceived(QSharedPointer<BaseMessage> msg);
	void messageSent(QSharedPointer<BaseMessage> msg);

private slots:
	void initialize();
};

#endif // MAINWINDOW_H
