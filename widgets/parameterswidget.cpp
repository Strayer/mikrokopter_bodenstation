#include "parameterswidget.h"
#include "helper_functions.h"
#include "messages/all_messages.h"
#include "messages/parameter_type_ids.h"

#include <QtGui>
#include <QSharedPointer>

#define create_parameter_widget(param_id, layout) { \
	ParameterControlWidget *param_widget = new ParameterControlWidget(param_id, this); \
	m_parameterControlWidgets.insert(param_id, param_widget); \
	layout->addWidget(param_widget); \
	m_signalMapper->setMapping(param_widget, param_widget); \
	connect(param_widget, SIGNAL(editingFinished()), m_signalMapper, SLOT(map())); \
}

ParametersWidget::ParametersWidget(MainWindow *mainWindow, QWidget *parent) :
	QWidget(parent), m_mainWindow(mainWindow)
{
	m_dirty = false;
	QHBoxLayout *parameterGroupsLayout = new QHBoxLayout(parent);
	m_signalMapper = new QSignalMapper(this);
	connect(m_signalMapper, SIGNAL(mapped(QWidget*)), this, SLOT(parameterChanged(QWidget*)));
	this->m_settings = new QSettings(qApp->applicationDirPath().append("/parameter_profiles.ini"), QSettings::IniFormat);

	QGroupBox *yawBox = new QGroupBox(tr("YAW"));
	QVBoxLayout *yawLayout = new QVBoxLayout();
	yawBox->setLayout(yawLayout);

	create_parameter_widget(Parameters::YAW_KP, yawLayout);
	create_parameter_widget(Parameters::YAW_KI, yawLayout);
	create_parameter_widget(Parameters::YAW_KD, yawLayout);
	create_parameter_widget(Parameters::YAW_ILIMIT, yawLayout);
	create_parameter_widget(Parameters::YAW_RESOLUTIONFILTER, yawLayout);
	create_parameter_widget(Parameters::YAW_AVERAGINGFILTER, yawLayout);

	yawLayout->addStretch();

	QGroupBox *rollBox = new QGroupBox(tr("ROLL"));
	QVBoxLayout *rollLayout = new QVBoxLayout();
	rollBox->setLayout(rollLayout);

	create_parameter_widget(Parameters::ROLL_KP, rollLayout);
	create_parameter_widget(Parameters::ROLL_KI, rollLayout);
	create_parameter_widget(Parameters::ROLL_KD, rollLayout);
	create_parameter_widget(Parameters::ROLL_ILIMIT, rollLayout);
	create_parameter_widget(Parameters::ROLL_RESOLUTIONFILTER, rollLayout);
	create_parameter_widget(Parameters::ROLL_AVERAGINGFILTER, rollLayout);

	rollLayout->addStretch();

	QGroupBox *pitchBox = new QGroupBox(tr("PITCH"));
	QVBoxLayout *pitchLayout = new QVBoxLayout();
	pitchBox->setLayout(pitchLayout);

	create_parameter_widget(Parameters::PITCH_KP, pitchLayout);
	create_parameter_widget(Parameters::PITCH_KI, pitchLayout);
	create_parameter_widget(Parameters::PITCH_KD, pitchLayout);
	create_parameter_widget(Parameters::PITCH_ILIMIT, pitchLayout);
	create_parameter_widget(Parameters::PITCH_RESOLUTIONFILTER, pitchLayout);
	create_parameter_widget(Parameters::PITCH_AVERAGINGFILTER, pitchLayout);

	pitchLayout->addStretch();

	QGroupBox *miscBox = new QGroupBox(tr("MISC"));
	QVBoxLayout *miscLayout = new QVBoxLayout();
	miscBox->setLayout(miscLayout);

	create_parameter_widget(Parameters::MISC_ACC_HORIZ_KI, miscLayout);
	create_parameter_widget(Parameters::MISC_ACC_VERT_KI, miscLayout);
	create_parameter_widget(Parameters::MISC_COMPASS_KI, miscLayout);
	create_parameter_widget(Parameters::MISC_IDLE_SPEED, miscLayout);
	create_parameter_widget(Parameters::MISC_START_THRESHOLD, miscLayout);
	create_parameter_widget(Parameters::MISC_STOP_THRESHOLD, miscLayout);
	create_parameter_widget(Parameters::MISC_SKIP_CONTROL_CYCLES, miscLayout);
	create_parameter_widget(Parameters::MISC_ACC_RANGE, miscLayout);

	miscLayout->addStretch();

	QGroupBox *specialBox = new QGroupBox(tr("SPECIAL"));
	QVBoxLayout *specialLayout = new QVBoxLayout();
	specialBox->setLayout(specialLayout);

	create_parameter_widget(Parameters::SPECIAL_BATT_VOLTAGE, specialLayout);

	specialLayout->addStretch();

	parameterGroupsLayout->addWidget(yawBox);
	parameterGroupsLayout->addWidget(rollBox);
	parameterGroupsLayout->addWidget(pitchBox);
	parameterGroupsLayout->addWidget(miscBox);
	parameterGroupsLayout->addWidget(specialBox);

	// Buttons

	m_profileButton = new QToolButton();
	m_profileButton->setArrowType(Qt::DownArrow);
	m_profileButton->setMenu(new QMenu());
	m_profileButton->setPopupMode(QToolButton::MenuButtonPopup);
	m_profileButton->setToolButtonStyle(Qt::ToolButtonTextOnly);

	QPushButton *getParametersButton = new QPushButton(tr("Parameter abfragen"));
	m_sendParametersButton = new QPushButton(tr("Parameter senden"));

	QHBoxLayout *buttonLayout = new QHBoxLayout();
	buttonLayout->addStretch();
	buttonLayout->addWidget(m_profileButton);
	buttonLayout->addWidget(getParametersButton);
	buttonLayout->addWidget(m_sendParametersButton);

	connect(m_profileButton, SIGNAL(triggered(QAction*)), this, SLOT(changeProfile(QAction*)));
	connect(m_profileButton, SIGNAL(clicked()), this, SLOT(saveProfile()));
	connect(getParametersButton, SIGNAL(clicked()), this, SLOT(getParameters()));
	connect(m_sendParametersButton, SIGNAL(clicked()), this, SLOT(sendParameters()));

	// Hauptlayout

	QVBoxLayout *mainLayout = new QVBoxLayout();
	mainLayout->addLayout(parameterGroupsLayout);
	mainLayout->addLayout(buttonLayout);
	setLayout(mainLayout);

	rebuildProfileMenu();
	changeProfile(m_profileButton->menu()->defaultAction());
}

ParametersWidget::~ParametersWidget()
{
	delete m_settings;
}

void ParametersWidget::getParameters()
{
	foreach (ParameterControlWidget *le, m_parameterControlWidgets)
	{
		auto msg = QSharedPointer<GetParameterMessage>(new GetParameterMessage(le->parameterTypeId()));
		auto proxymsg = QSharedPointer<ProxyMessage>(new ProxyMessage());
		proxymsg->setInnerMessage(msg);
		m_mainWindow->enqueueMessage(proxymsg);
		le->setDisabled(true);
	}
}

void ParametersWidget::sendParameters()
{
	foreach (ParameterControlWidget *le, m_parameterControlWidgets)
	{
		auto msg = QSharedPointer<SetParameterMessage>(new SetParameterMessage(le->parameterTypeId(), le->value()));
		auto proxymsg = QSharedPointer<ProxyMessage>(new ProxyMessage());
		proxymsg->setInnerMessage(msg);
		m_mainWindow->enqueueMessage(proxymsg);
		le->setDisabled(true);
	}
}

void ParametersWidget::changeProfile(QAction *action)
{
	QString profile = action->data().toString();
	if (profile.isNull()) return;
	m_activeProfileAction = action;

	if (isDirty())
	{
		QMessageBox msgBox;
		msgBox.setText(tr("Das aktuelle Profil hat ungesicherte Änderungen."));
		msgBox.setInformativeText("Sollen die Änderungen im Profil gespeichert werden?");
		msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
		msgBox.setDefaultButton(QMessageBox::Save);
		int ret = msgBox.exec();

		if (ret == QMessageBox::Cancel)
			return;
		else if (ret == QMessageBox::Save)
			saveProfile();
	}

	setDirty(false);

	if (profile == "new_profile")
	{
		bool ok;
		QString text = QInputDialog::getText(this, tr("Neues Profil"), tr("Name:"), QLineEdit::Normal, "", &ok);

		if (ok && !text.isEmpty())
		{
			QUuid profileUuid = QUuid::createUuid();

			m_settings->beginGroup(profileUuid.toString());
			m_settings->setValue("profileName", text);

			m_settings->beginGroup("parameters");
			foreach (ParameterControlWidget *le, m_parameterControlWidgets)
				m_settings->setValue(ParameterTypeIdToString(le->parameterTypeId()), le->value());
			m_settings->endGroup();

			m_settings->endGroup();

			rebuildProfileMenu();

			// Action finden und auswählen
			foreach (QAction *action, m_profileButton->menu()->actions())
			{
				if (action->data().toString() == profileUuid.toString())
				{
					changeProfile(action);
					return;
				}
			}
		}
	}
	else
	{
		m_profileButton->setText(QString("%1: %2").arg(tr("Profil")).arg(action->text()));
		bool readOnly = (profile == "read_only");
		m_activeProfile = profile;

		m_sendParametersButton->setDisabled(readOnly);

		foreach (ParameterControlWidget *le, m_parameterControlWidgets)
		{
			le->setReadOnly(readOnly);
			le->setValue(0);
		}

		if (profile.startsWith("{"))
		{
			QUuid profileUuid = QUuid(profile);
			if (profileUuid.isNull()) return;

			m_settings->beginGroup(profileUuid.toString());
			m_settings->beginGroup("parameters");
			foreach (ParameterControlWidget *le, m_parameterControlWidgets)
			{
				le->setValue(m_settings->value(ParameterTypeIdToString(le->parameterTypeId())).toInt());
			}
			m_settings->endGroup();
			m_settings->endGroup();
		}
	}
}

void ParametersWidget::rebuildProfileMenu()
{
	QMenu *profileButtonMenu = m_profileButton->menu();
	profileButtonMenu->clear();

	QAction *readOnlyAction = new QAction(tr("Read-only"), profileButtonMenu);
	readOnlyAction->setData("read_only");
	profileButtonMenu->addAction(readOnlyAction);
	profileButtonMenu->addSeparator();

	foreach (QString le, m_settings->childGroups())
	{
		QAction *action = new QAction(m_settings->value(QString("%1/%2").arg(le).arg("profileName")).toString(), profileButtonMenu);
		action->setData(le);
		profileButtonMenu->addAction(action);
	}

	profileButtonMenu->addSeparator();
	QAction *newProfileAction = new QAction(tr("Neues Profil..."), profileButtonMenu);
	newProfileAction->setData("new_profile");
	profileButtonMenu->addAction(newProfileAction);
	profileButtonMenu->setDefaultAction(readOnlyAction);
}

void ParametersWidget::setParameterSpinBoxValue(int parameterTypeId, int newValue)
{
	if (m_parameterControlWidgets.contains(parameterTypeId))
	{
		m_parameterControlWidgets.value(parameterTypeId)->setValue(newValue);
		m_parameterControlWidgets.value(parameterTypeId)->setReadOnly(m_activeProfileAction->data().toString() == "read_only");
		m_parameterControlWidgets.value(parameterTypeId)->setDisabled(false);
	}
}

void ParametersWidget::saveProfile()
{
	if (m_activeProfile.startsWith("{"))
	{
		setDirty(false);
		m_settings->beginGroup(m_activeProfile);
		m_settings->beginGroup("parameters");
		foreach (ParameterControlWidget *le, m_parameterControlWidgets)
			m_settings->setValue(ParameterTypeIdToString(le->parameterTypeId()), le->value());
		m_settings->endGroup();
		m_settings->endGroup();
	}
}

void ParametersWidget::setDirty(bool toggle)
{
	m_dirty = toggle;

	if (m_dirty)
		m_profileButton->setText(QString("%1: %2*").arg(tr("Profil")).arg(m_activeProfileAction->text()));
	else
		m_profileButton->setText(QString("%1: %2").arg(tr("Profil")).arg(m_activeProfileAction->text()));
}

void ParametersWidget::parameterChanged(QWidget *widget)
{
	// Da hier auf editingFinished gehorcht wird wird die Funktion auch ausgeführt wenn im read_only-Modus eine Spinbox den Fokus verliert
	// Dabei darf natürlich nichts gesendet werden
	if (m_activeProfile == "read_only")
		return;

	ParameterControlWidget *parameterSpinBox = qobject_cast<ParameterControlWidget*>(widget);

	auto msg = QSharedPointer<SetParameterMessage>(new SetParameterMessage(parameterSpinBox->parameterTypeId(), parameterSpinBox->value()));
	auto proxymsg = QSharedPointer<ProxyMessage>(new ProxyMessage());
	proxymsg->setInnerMessage(msg);
	m_mainWindow->enqueueMessage(proxymsg);

	setDirty(true);
}

bool ParametersWidget::isDirty()
{
	return m_dirty;
}
