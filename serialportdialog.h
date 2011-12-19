#ifndef SERIALPORTDIALOG_H
#define SERIALPORTDIALOG_H

#include <QDialog>

#include "SerialPort.h"

namespace Ui {
class SerialPortDialog;
}

class SerialPortDialog : public QDialog
{
	Q_OBJECT

public:
	explicit SerialPortDialog(QWidget *parent = 0);
	~SerialPortDialog();

	SerialPort getSelectedSerialPort();

private:
	Ui::SerialPortDialog *ui;

private slots:
	void findSerialPorts();
};

#endif // SERIALPORTDIALOG_H
