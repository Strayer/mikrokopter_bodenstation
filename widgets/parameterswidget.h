#ifndef PARAMETERSWIDGET_H
#define PARAMETERSWIDGET_H

#include <QMap>
#include <QString>
#include <QWidget>
#include <QSpinBox>
#include "mainwindow.h"

class QToolButton;
class QPushButton;

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
	~ParametersWidget();

	void setParameterSpinBoxValue(int parameterTypeId, int newValue);

private:
	QList<ParameterSpinBox*> m_parameterSpinBoxes;
	MainWindow *m_mainWindow;
	QToolButton *profileButton;
	QPushButton *sendParametersButton;
	QSettings *settings;

	QString activeProfile;

	void rebuildProfileMenu();

signals:

public slots:
	void sendParameters();
	void getParameters();
	void changeProfile(QAction *action);
	void saveProfile();
};

#endif // PARAMETERSWIDGET_H
