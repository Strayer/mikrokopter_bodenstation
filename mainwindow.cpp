#include "mainwindow.h"
#include "serialportdialog.h"

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

    qDebug() << dlg->getSelectedSerialPort();
}
