#include "serialportdialog.h"
#include "ui_serialportdialog.h"

#include <vector>
#include <string>
#include "enumser.h"

#include <QVector>
#include <QTimer>
#include <QMessageBox>
#include <QDebug>

SerialPortDialog::SerialPortDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::SerialPortDialog)
{
	ui->setupUi(this);
	QTimer::singleShot(0, this, SLOT(findSerialPorts()));
}

SerialPortDialog::~SerialPortDialog()
{
	delete ui;
}

void SerialPortDialog::findSerialPorts()
{
	// Ports mit Enumser suchen
	std::vector<std::wstring> friendlyNames;
	std::vector<uint> ports;
	CEnumerateSerial::UsingSetupAPI2(ports, friendlyNames);

	// Wenns keine Ports gibt Fehlermeldung anzeigen und abbrechen
	if (ports.size() == 0)
	{
		QMessageBox::critical(this,
							  tr("Keine seriellen Ports gefunden"),
							  tr("Leider wurden keine seriellen Ports gefunden. Bitte überprüfen Sie die Verbindung zum Funkmodul."));
		this->reject();
		return;
	}

	ui->comboBox->clear();

	for (uint i = 0; i < ports.size(); i++)
	{
		QString label = QString("COM%1 (%2)").arg(ports.at(i)).arg(QString::fromStdWString(friendlyNames.at(i)));
		SerialPort port = SerialPort(ports.at(i), friendlyNames.at(i));
		ui->comboBox->addItem(label, QVariant::fromValue(port));
	}

	ui->comboBox->setEnabled(true);
	ui->label->setEnabled(true);
	ui->buttonBox->setEnabled(true);
}

SerialPort SerialPortDialog::getSelectedSerialPort()
{
	return ui->comboBox->itemData(ui->comboBox->currentIndex()).value<SerialPort>();
}
