#ifndef PARAMETERSWIDGET_H
#define PARAMETERSWIDGET_H

#include <QMap>
#include <QString>
#include <QWidget>
#include <QSpinBox>
#include "mainwindow.h"

class QToolButton;
class QPushButton;
class QAction;
class QSignalMapper;

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

	void setParameterSpinBoxValue(int parameterTypeId, int newValue, bool dontSetDirty = false);

	bool isDirty();
	void setDirty(bool toggle);

private:
	QList<ParameterSpinBox*> m_parameterSpinBoxes;
	MainWindow *m_mainWindow;
	QToolButton *m_profileButton;
	QPushButton *m_sendParametersButton;
	QSettings *m_settings;
	bool m_dirty;
	QSignalMapper *m_signalMapper;

	QString m_activeProfile;
	QAction *m_activeProfileAction;

	void rebuildProfileMenu();

signals:

public slots:
	void sendParameters();
	void getParameters();
	void changeProfile(QAction *action);
	void saveProfile();
	void parameterChanged(QWidget *widget);
};

#endif // PARAMETERSWIDGET_H
