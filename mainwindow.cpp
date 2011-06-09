#include "mainwindow.h"
#include "serialportdialog.h"

#include "serialporthandler.h"

#include <QTimer>
#include <QDebug>

#include <QtGui>
#include <QtCore>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent)
{
	setWindowIcon(QIcon(":/icons/app-icon"));
	setWindowTitle(tr("Bodenstation-Ork"));
	setMinimumWidth(500);

	restoreGeometry(settings.value("window/geometry").toByteArray());

	// Erstmal müssen wir uns einen Serial Port holen
	SerialPortDialog *dlg = new SerialPortDialog(this);
	if (dlg->exec() == QDialog::Rejected)
	{
		QTimer::singleShot(0, this, SLOT(close()));
		return;
	}

	SerialPort port = dlg->getSelectedSerialPort();
	serial = new SerialPortHandler(port);
	serial->moveToThread(&serialPortThread);
	connect(&serialPortThread, SIGNAL(started()), serial, SLOT(start()));
	connect(serial, SIGNAL(newMessageReceived(QSharedPointer<BaseMessage>)), this, SLOT(newMessageReceived(QSharedPointer<BaseMessage>)));
	connect(serial, SIGNAL(messageSent(QSharedPointer<BaseMessage>)), this, SLOT(messageSent(QSharedPointer<BaseMessage>)));
	serialPortThread.start();

	QVBoxLayout *layout = new QVBoxLayout();

	msgList = new QListWidget();
	layout->addWidget(msgList);
	QPushButton *button = new QPushButton();
	button->setText("Ping senden");
	layout->addWidget(button);

	setCentralWidget(new QWidget());
	centralWidget()->setLayout(layout);

	connect(button, SIGNAL(clicked()), this, SLOT(buttonClicked()));
}

void MainWindow::buttonClicked()
{
	//for (int i = 0; i < 2000; i++)
	serial->sendTestPing();
}

void MainWindow::newMessageReceived(QSharedPointer<BaseMessage> msg)
{
	bool scrollDown = false;
	if (msgList->verticalScrollBar()->sliderPosition() == msgList->verticalScrollBar()->maximum())
		scrollDown = true;

	msgList->addItem(new QListWidgetItem(QIcon(":/icons/arrow-left"), QString("%1: %2").arg(QDateTime::currentDateTime().toString()).arg(msg->toString())));

	if (scrollDown)
		msgList->scrollToBottom();
}

void MainWindow::messageSent(QSharedPointer<BaseMessage> msg)
{
	bool scrollDown = false;
	if (msgList->verticalScrollBar()->sliderPosition() == msgList->verticalScrollBar()->maximum())
		scrollDown = true;

	msgList->addItem(new QListWidgetItem(QIcon(":/icons/arrow-right"), QString("%1: %2").arg(QDateTime::currentDateTime().toString()).arg(msg->toString())));

	if (scrollDown)
		msgList->scrollToBottom();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
	settings.setValue("window/geometry", saveGeometry());
}
