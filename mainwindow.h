#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class SerialPortHandler;

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	explicit MainWindow(QWidget *parent = 0);

private:
	SerialPortHandler *serial;

signals:

public slots:
	void buttonClicked();

};

#endif // MAINWINDOW_H
