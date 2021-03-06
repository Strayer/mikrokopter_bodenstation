#include "mainwindow.h"
#include "serialportdialog.h"

#include "serialporthandler.h"
#include "decimaldebughandler.h"

#include <QTimer>
#include <QDebug>

#include <QtGui>
#include <QtCore>

//#include <widgets/camerawidget.h>
#include <widgets/parameterswidget.h>
#include <widgets/bigparameterdisplaywidget.h>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent)
{
	setWindowIcon(QIcon(":/icons/app-icon"));
	setWindowTitle(tr("Bodenstation-Ork"));
	setMinimumWidth(500);

	QAction *quitAction = new QAction(this);
	quitAction->setText(tr("&Beenden"));
	connect(quitAction, SIGNAL(triggered()), this, SLOT(close()));

	QAction *bigNumbersWindowAction = new QAction(this);
	bigNumbersWindowAction->setText(tr("Gro�e &Zahlen Fenster"));
	connect(bigNumbersWindowAction, SIGNAL(triggered()), this, SLOT(createBigNumbersDisplay()));

	QMenu *fileMenu = menuBar()->addMenu(tr("&Datei"));
	fileMenu->addAction(quitAction);

	QMenu *viewMenu = menuBar()->addMenu(tr("&Ansicht"));
	viewMenu->addAction(bigNumbersWindowAction);

	QTimer::singleShot(0, this, SLOT(initialize()));
}

void MainWindow::sendPingButtonClicked()
{
	auto msg = QSharedPointer<BaseMessage>(new PingMessage());
	serial->enqueueMessage(msg);
}

void MainWindow::sendProxyPingButtonClicked()
{
	auto msg = QSharedPointer<BaseMessage>(new PingMessage());
	auto msg2 = QSharedPointer<ProxyMessage>(new ProxyMessage());
	msg2->setInnerMessage(msg);
	serial->enqueueMessage(msg2);
}

void MainWindow::newMessageReceived(QSharedPointer<BaseMessage> msg)
{
	if (msg->messageType() == BaseMessage::MessageTypes::DECIMAL_DEBUG_DUMP)
		return;

	bool scrollDown = false;

	if (msgList->count() > 300)
		msgList->takeItem(0);
	else
	{
		// Das mitscrollen ist nur sinnvoll solange die Liste nicht voll ist
		if (msgList->verticalScrollBar()->sliderPosition() == msgList->verticalScrollBar()->maximum())
			scrollDown = true;
	}

	msgList->addItem(new QListWidgetItem(QIcon(":/icons/arrow-left"), QString("%1: %2").arg(QDateTime::currentDateTime().toString()).arg(msg->toString())));

	if (msg->messageType() == BaseMessage::MessageTypes::CUR_PARAMETER)
	{
		QSharedPointer<CurParameterMessage> curParameterMsg = msg.staticCast<CurParameterMessage>();
		parametersWidget->setParameterSpinBoxValue(curParameterMsg->parameterTypeId(), curParameterMsg->value());
	}

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

void MainWindow::closeEvent(QCloseEvent *)
{
	settings.setValue("window/geometry", saveGeometry());
}

void MainWindow::enqueueMessage(QSharedPointer<BaseMessage> msg)
{
	serial->enqueueMessage(msg);
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_F11)
		setWindowState(windowState() ^ Qt::WindowFullScreen);
	else
		QMainWindow::keyReleaseEvent(event);
}

void MainWindow::initialize()
{
	restoreGeometry(settings.value("window/geometry").toByteArray());

	// Erstmal m�ssen wir uns einen Serial Port holen
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

	DecimalDebugHandler *decimalDebugHandler = new DecimalDebugHandler();
	decimalDebugHandler->moveToThread(&decimalDebugThread);
	connect(&decimalDebugThread, SIGNAL(started()), decimalDebugHandler, SLOT(start()));
	connect(serial, SIGNAL(newMessageReceived(QSharedPointer<BaseMessage>)), decimalDebugHandler, SLOT(newMessageReceived(QSharedPointer<BaseMessage>)));
	decimalDebugThread.start();

	QVBoxLayout *layout = new QVBoxLayout();

	msgList = new QListWidget();
	layout->addWidget(msgList);

	QHBoxLayout *buttonLayout = new QHBoxLayout();
	QPushButton *button2 = new QPushButton();
	button2->setText("ProxyPing senden");
	buttonLayout->addWidget(button2);
	QPushButton *button = new QPushButton();
	button->setText("Ping senden");
	buttonLayout->addWidget(button);
	layout->addLayout(buttonLayout);

	parametersWidget = new ParametersWidget(this);
	layout->addWidget(parametersWidget);

	//CameraWidget *cameraWidget = new CameraWidget();
	//layout->addWidget(cameraWidget, 0, Qt::AlignCenter);

	setCentralWidget(new QWidget());
	centralWidget()->setLayout(layout);

	connect(button, SIGNAL(clicked()), this, SLOT(sendPingButtonClicked()));
	connect(button2, SIGNAL(clicked()), this, SLOT(sendProxyPingButtonClicked()));
}

void MainWindow::createBigNumbersDisplay()
{
	BigParameterDisplayWidget *blaaa = new BigParameterDisplayWidget(serial);
	blaaa->show();
}
