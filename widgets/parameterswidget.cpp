#include "parameterswidget.h"
#include "helper_functions.h"
#include "messages/all_messages.h"
#include "messages/parameter_type_ids.h"

#include <QtGui>
#include <QSharedPointer>

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

	ParameterControlWidget *YAW_KP = new ParameterControlWidget(Parameters::YAW_KP, this);
	m_parameterControlWidgets.append(YAW_KP);
	yawLayout->addWidget(YAW_KP);
	m_signalMapper->setMapping(YAW_KP, YAW_KP);
	connect(YAW_KP, SIGNAL(editingFinished()), m_signalMapper, SLOT(map()));

	ParameterControlWidget *YAW_KI = new ParameterControlWidget(Parameters::YAW_KI, this);
	m_parameterControlWidgets.append(YAW_KI);
	yawLayout->addWidget(YAW_KI);
	m_signalMapper->setMapping(YAW_KI, YAW_KI);
	connect(YAW_KI, SIGNAL(editingFinished()), m_signalMapper, SLOT(map()));

	ParameterControlWidget *YAW_KD = new ParameterControlWidget(Parameters::YAW_KD, this);
	m_parameterControlWidgets.append(YAW_KD);
	yawLayout->addWidget(YAW_KD);
	m_signalMapper->setMapping(YAW_KD, YAW_KD);
	connect(YAW_KD, SIGNAL(editingFinished()), m_signalMapper, SLOT(map()));

	ParameterControlWidget *YAW_ILIMIT = new ParameterControlWidget(Parameters::YAW_ILIMIT, this);
	m_parameterControlWidgets.append(YAW_ILIMIT);
	yawLayout->addWidget(YAW_ILIMIT);
	m_signalMapper->setMapping(YAW_ILIMIT, YAW_ILIMIT);
	connect(YAW_ILIMIT, SIGNAL(editingFinished()), m_signalMapper, SLOT(map()));

	ParameterControlWidget *YAW_RESOLUTIONFILTER = new ParameterControlWidget(Parameters::YAW_RESOLUTIONFILTER, this);
	m_parameterControlWidgets.append(YAW_RESOLUTIONFILTER);
	yawLayout->addWidget(YAW_RESOLUTIONFILTER);
	m_signalMapper->setMapping(YAW_RESOLUTIONFILTER, YAW_RESOLUTIONFILTER);
	connect(YAW_RESOLUTIONFILTER, SIGNAL(editingFinished()), m_signalMapper, SLOT(map()));

	ParameterControlWidget *YAW_AVERAGINGFILTER = new ParameterControlWidget(Parameters::YAW_AVERAGINGFILTER, this);
	m_parameterControlWidgets.append(YAW_AVERAGINGFILTER);
	yawLayout->addWidget(YAW_AVERAGINGFILTER);
	m_signalMapper->setMapping(YAW_AVERAGINGFILTER, YAW_AVERAGINGFILTER);
	connect(YAW_AVERAGINGFILTER, SIGNAL(editingFinished()), m_signalMapper, SLOT(map()));

	yawLayout->addStretch();

	QGroupBox *rollBox = new QGroupBox(tr("ROLL"));
	QVBoxLayout *rollLayout = new QVBoxLayout();
	rollBox->setLayout(rollLayout);

	ParameterControlWidget *ROLL_KP = new ParameterControlWidget(Parameters::ROLL_KP, this);
	m_parameterControlWidgets.append(ROLL_KP);
	rollLayout->addWidget(ROLL_KP);
	m_signalMapper->setMapping(ROLL_KP, ROLL_KP);
	connect(ROLL_KP, SIGNAL(editingFinished()), m_signalMapper, SLOT(map()));

	ParameterControlWidget *ROLL_KI = new ParameterControlWidget(Parameters::ROLL_KI, this);
	m_parameterControlWidgets.append(ROLL_KI);
	rollLayout->addWidget(ROLL_KI);
	m_signalMapper->setMapping(ROLL_KI, ROLL_KI);
	connect(ROLL_KI, SIGNAL(editingFinished()), m_signalMapper, SLOT(map()));

	ParameterControlWidget *ROLL_KD = new ParameterControlWidget(Parameters::ROLL_KD, this);
	m_parameterControlWidgets.append(ROLL_KD);
	rollLayout->addWidget(ROLL_KD);
	m_signalMapper->setMapping(ROLL_KD, ROLL_KD);
	connect(ROLL_KD, SIGNAL(editingFinished()), m_signalMapper, SLOT(map()));

	ParameterControlWidget *ROLL_ILIMIT = new ParameterControlWidget(Parameters::ROLL_ILIMIT, this);
	m_parameterControlWidgets.append(ROLL_ILIMIT);
	rollLayout->addWidget(ROLL_ILIMIT);
	m_signalMapper->setMapping(ROLL_ILIMIT, ROLL_ILIMIT);
	connect(ROLL_ILIMIT, SIGNAL(editingFinished()), m_signalMapper, SLOT(map()));

	ParameterControlWidget *ROLL_RESOLUTIONFILTER = new ParameterControlWidget(Parameters::ROLL_RESOLUTIONFILTER, this);
	m_parameterControlWidgets.append(ROLL_RESOLUTIONFILTER);
	rollLayout->addWidget(ROLL_RESOLUTIONFILTER);
	m_signalMapper->setMapping(ROLL_RESOLUTIONFILTER, ROLL_RESOLUTIONFILTER);
	connect(ROLL_RESOLUTIONFILTER, SIGNAL(editingFinished()), m_signalMapper, SLOT(map()));

	ParameterControlWidget *ROLL_AVERAGINGFILTER = new ParameterControlWidget(Parameters::ROLL_AVERAGINGFILTER, this);
	m_parameterControlWidgets.append(ROLL_AVERAGINGFILTER);
	rollLayout->addWidget(ROLL_AVERAGINGFILTER);
	m_signalMapper->setMapping(ROLL_AVERAGINGFILTER, ROLL_AVERAGINGFILTER);
	connect(ROLL_AVERAGINGFILTER, SIGNAL(editingFinished()), m_signalMapper, SLOT(map()));

	rollLayout->addStretch();

	QGroupBox *pitchBox = new QGroupBox(tr("PITCH"));
	QVBoxLayout *pitchLayout = new QVBoxLayout();
	pitchBox->setLayout(pitchLayout);

	ParameterControlWidget *PITCH_KP = new ParameterControlWidget(Parameters::PITCH_KP, this);
	m_parameterControlWidgets.append(PITCH_KP);
	pitchLayout->addWidget(PITCH_KP);
	m_signalMapper->setMapping(PITCH_KP, PITCH_KP);
	connect(PITCH_KP, SIGNAL(editingFinished()), m_signalMapper, SLOT(map()));

	ParameterControlWidget *PITCH_KI = new ParameterControlWidget(Parameters::PITCH_KI, this);
	m_parameterControlWidgets.append(PITCH_KI);
	pitchLayout->addWidget(PITCH_KI);
	m_signalMapper->setMapping(PITCH_KI, PITCH_KI);
	connect(PITCH_KI, SIGNAL(editingFinished()), m_signalMapper, SLOT(map()));

	ParameterControlWidget *PITCH_KD = new ParameterControlWidget(Parameters::PITCH_KD, this);
	m_parameterControlWidgets.append(PITCH_KD);
	pitchLayout->addWidget(PITCH_KD);
	m_signalMapper->setMapping(PITCH_KD, PITCH_KD);
	connect(PITCH_KD, SIGNAL(editingFinished()), m_signalMapper, SLOT(map()));

	ParameterControlWidget *PITCH_ILIMIT = new ParameterControlWidget(Parameters::PITCH_ILIMIT, this);
	m_parameterControlWidgets.append(PITCH_ILIMIT);
	pitchLayout->addWidget(PITCH_ILIMIT);
	m_signalMapper->setMapping(PITCH_ILIMIT, PITCH_ILIMIT);
	connect(PITCH_ILIMIT, SIGNAL(editingFinished()), m_signalMapper, SLOT(map()));

	ParameterControlWidget *PITCH_RESOLUTIONFILTER = new ParameterControlWidget(Parameters::PITCH_RESOLUTIONFILTER, this);
	m_parameterControlWidgets.append(PITCH_RESOLUTIONFILTER);
	pitchLayout->addWidget(PITCH_RESOLUTIONFILTER);
	m_signalMapper->setMapping(PITCH_RESOLUTIONFILTER, PITCH_RESOLUTIONFILTER);
	connect(PITCH_RESOLUTIONFILTER, SIGNAL(editingFinished()), m_signalMapper, SLOT(map()));

	ParameterControlWidget *PITCH_AVERAGINGFILTER = new ParameterControlWidget(Parameters::PITCH_AVERAGINGFILTER, this);
	m_parameterControlWidgets.append(PITCH_AVERAGINGFILTER);
	pitchLayout->addWidget(PITCH_AVERAGINGFILTER);
	m_signalMapper->setMapping(PITCH_AVERAGINGFILTER, PITCH_AVERAGINGFILTER);
	connect(PITCH_AVERAGINGFILTER, SIGNAL(editingFinished()), m_signalMapper, SLOT(map()));

	pitchLayout->addStretch();

	QGroupBox *miscBox = new QGroupBox(tr("MISC"));
	QVBoxLayout *miscLayout = new QVBoxLayout();
	miscBox->setLayout(miscLayout);

	ParameterControlWidget *MISC_ACC_HORIZ_KI = new ParameterControlWidget(Parameters::MISC_ACC_HORIZ_KI, this);
	m_parameterControlWidgets.append(MISC_ACC_HORIZ_KI);
	miscLayout->addWidget(MISC_ACC_HORIZ_KI);
	m_signalMapper->setMapping(MISC_ACC_HORIZ_KI, MISC_ACC_HORIZ_KI);
	connect(MISC_ACC_HORIZ_KI, SIGNAL(editingFinished()), m_signalMapper, SLOT(map()));

	ParameterControlWidget *MISC_ACC_VERT_KI = new ParameterControlWidget(Parameters::MISC_ACC_VERT_KI, this);
	m_parameterControlWidgets.append(MISC_ACC_VERT_KI);
	miscLayout->addWidget(MISC_ACC_VERT_KI);
	m_signalMapper->setMapping(MISC_ACC_VERT_KI, MISC_ACC_VERT_KI);
	connect(MISC_ACC_VERT_KI, SIGNAL(editingFinished()), m_signalMapper, SLOT(map()));

	ParameterControlWidget *MISC_COMPASS_KI = new ParameterControlWidget(Parameters::MISC_COMPASS_KI, this);
	m_parameterControlWidgets.append(MISC_COMPASS_KI);
	miscLayout->addWidget(MISC_COMPASS_KI);
	m_signalMapper->setMapping(MISC_COMPASS_KI, MISC_COMPASS_KI);
	connect(MISC_COMPASS_KI, SIGNAL(editingFinished()), m_signalMapper, SLOT(map()));

	ParameterControlWidget *MISC_IDLE_SPEED = new ParameterControlWidget(Parameters::MISC_IDLE_SPEED, this);
	m_parameterControlWidgets.append(MISC_IDLE_SPEED);
	miscLayout->addWidget(MISC_IDLE_SPEED);
	m_signalMapper->setMapping(MISC_IDLE_SPEED, MISC_IDLE_SPEED);
	connect(MISC_IDLE_SPEED, SIGNAL(editingFinished()), m_signalMapper, SLOT(map()));

	ParameterControlWidget *MISC_START_THRESHOLD = new ParameterControlWidget(Parameters::MISC_START_THRESHOLD, this);
	m_parameterControlWidgets.append(MISC_START_THRESHOLD);
	miscLayout->addWidget(MISC_START_THRESHOLD);
	m_signalMapper->setMapping(MISC_START_THRESHOLD, MISC_START_THRESHOLD);
	connect(MISC_START_THRESHOLD, SIGNAL(editingFinished()), m_signalMapper, SLOT(map()));

	ParameterControlWidget *MISC_STOP_THRESHOLD = new ParameterControlWidget(Parameters::MISC_STOP_THRESHOLD, this);
	m_parameterControlWidgets.append(MISC_STOP_THRESHOLD);
	miscLayout->addWidget(MISC_STOP_THRESHOLD);
	m_signalMapper->setMapping(MISC_STOP_THRESHOLD, MISC_STOP_THRESHOLD);
	connect(MISC_STOP_THRESHOLD, SIGNAL(editingFinished()), m_signalMapper, SLOT(map()));

	ParameterControlWidget *MISC_SKIP_CONTROL_CYCLES = new ParameterControlWidget(Parameters::MISC_SKIP_CONTROL_CYCLES, this);
	m_parameterControlWidgets.append(MISC_SKIP_CONTROL_CYCLES);
	miscLayout->addWidget(MISC_SKIP_CONTROL_CYCLES);
	m_signalMapper->setMapping(MISC_SKIP_CONTROL_CYCLES, MISC_SKIP_CONTROL_CYCLES);
	connect(MISC_SKIP_CONTROL_CYCLES, SIGNAL(editingFinished()), m_signalMapper, SLOT(map()));

	ParameterControlWidget *MISC_ACC_RANGE = new ParameterControlWidget(Parameters::MISC_ACC_RANGE, this);
	m_parameterControlWidgets.append(MISC_ACC_RANGE);
	miscLayout->addWidget(MISC_ACC_RANGE);
	m_signalMapper->setMapping(MISC_ACC_RANGE, MISC_ACC_RANGE);
	connect(MISC_ACC_RANGE, SIGNAL(editingFinished()), m_signalMapper, SLOT(map()));

	miscLayout->addStretch();

	QGroupBox *specialBox = new QGroupBox(tr("SPECIAL"));
	QVBoxLayout *specialLayout = new QVBoxLayout();
	specialBox->setLayout(specialLayout);

	ParameterControlWidget *SPECIAL_BATT_VOLTAGE = new ParameterControlWidget(Parameters::SPECIAL_BATT_VOLTAGE, this);
	m_parameterControlWidgets.append(SPECIAL_BATT_VOLTAGE);
	specialLayout->addWidget(SPECIAL_BATT_VOLTAGE);
	m_signalMapper->setMapping(SPECIAL_BATT_VOLTAGE, SPECIAL_BATT_VOLTAGE);
	connect(SPECIAL_BATT_VOLTAGE, SIGNAL(editingFinished()), m_signalMapper, SLOT(map()));

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
	foreach (ParameterControlWidget *le, m_parameterControlWidgets)
	{
		if (le->parameterTypeId() == parameterTypeId)
		{
			le->setValue(newValue);
			le->setReadOnly(m_activeProfileAction->data().toString() == "read_only");
			le->setDisabled(false);
			break;
		}
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
