#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>

class SerialPortHandler;

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	explicit MainWindow(QWidget *parent = 0);

private:
	SerialPortHandler *serial;
	QThread serialPortThread;

signals:

public slots:
	void buttonClicked();

};

#endif // MAINWINDOW_H
