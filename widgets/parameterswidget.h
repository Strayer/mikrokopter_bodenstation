#ifndef PARAMETERSWIDGET_H
#define PARAMETERSWIDGET_H

#include <QWidget>
#include <QMap>
#include <QString>
#include <QSpinBox>
#include "mainwindow.h"

class ParameterSpinBox : public QSpinBox
{
public:
	ParameterSpinBox(int parameterTypeId, QWidget *parent = 0) : QSpinBox(parent), m_parameterTypeId(parameterTypeId)
	{
		setMinimum(0);
		setMaximum(16777216);
	}

public:
	int parameterTypeId() { return m_parameterTypeId; }

private:
	int m_parameterTypeId;
};

class ParametersWidget : public QWidget
{
    Q_OBJECT
public:
	explicit ParametersWidget(MainWindow *mainWindow, QWidget *parent = 0);

private:
	QList<ParameterSpinBox*> m_parameterSpinBoxes;
	MainWindow *m_mainWindow;

signals:

public slots:
	void sendParameters();
	void getParameters();
};

#endif // PARAMETERSWIDGET_H
