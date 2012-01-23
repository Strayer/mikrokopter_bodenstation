#ifndef PARAMETERSWIDGET_H
#define PARAMETERSWIDGET_H

#include <QMap>
#include <QWidget>
#include "mainwindow.h"
#include "widgets/parametercontrolwidget.h"

class QToolButton;
class QPushButton;
class QAction;
class QSignalMapper;

class ParametersWidget : public QWidget
{
	Q_OBJECT
public:
	explicit ParametersWidget(MainWindow *mainWindow, QWidget *parent = 0);
	~ParametersWidget();

	void setParameterSpinBoxValue(int parameterTypeId, int newValue);

	bool isDirty();
	void setDirty(bool toggle);

private:
	QHash<int, ParameterControlWidget*> m_parameterControlWidgets;
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
