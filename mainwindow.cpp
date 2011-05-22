#include "mainwindow.h"
#include "serialportdialog.h"

#include "serialporthandler.h"

#include <QTimer>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent)
{
	// Erstmal müssen wir uns einen Serial Port holen
	SerialPortDialog *dlg = new SerialPortDialog(this);
	if (dlg->exec() == QDialog::Rejected)
	{
		QTimer::singleShot(0, this, SLOT(close()));
		return;
	}

	SerialPort port = dlg->getSelectedSerialPort();

	serial = new SerialPortHandler(port.friendlyName().toAscii().constData());
	serial->sendTestPing();
}
