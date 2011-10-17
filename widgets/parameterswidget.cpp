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

	QGroupBox *miscBox = new QGroupBox(tr("MISC"));
	QFormLayout *miscBoxLayout = new QFormLayout();
	miscBox->setLayout(miscBoxLayout);

	ParameterSpinBox *MISC_ACC_HORIZ_KI = new ParameterSpinBox(Parameters::MISC_ACC_HORIZ_KI);
	m_parameterSpinBoxes.append(MISC_ACC_HORIZ_KI);
	miscBoxLayout->addRow(tr("ACC_HORIZ_KI:"), MISC_ACC_HORIZ_KI);
	m_signalMapper->setMapping(MISC_ACC_HORIZ_KI, MISC_ACC_HORIZ_KI);
	connect(MISC_ACC_HORIZ_KI, SIGNAL(valueChanged(int)), m_signalMapper, SLOT(map()));

	ParameterSpinBox *MISC_ACC_RANGE = new ParameterSpinBox(Parameters::MISC_ACC_RANGE);
	m_parameterSpinBoxes.append(MISC_ACC_RANGE);
	miscBoxLayout->addRow(tr("ACC_RANGE:"), MISC_ACC_RANGE);
	m_signalMapper->setMapping(MISC_ACC_RANGE, MISC_ACC_RANGE);
	connect(MISC_ACC_RANGE, SIGNAL(valueChanged(int)), m_signalMapper, SLOT(map()));

	ParameterSpinBox *MISC_ACC_VERT_KI = new ParameterSpinBox(Parameters::MISC_ACC_VERT_KI);
	m_parameterSpinBoxes.append(MISC_ACC_VERT_KI);
	miscBoxLayout->addRow(tr("ACC_VERT_KI:"), MISC_ACC_VERT_KI);
	m_signalMapper->setMapping(MISC_ACC_VERT_KI, MISC_ACC_VERT_KI);
	connect(MISC_ACC_VERT_KI, SIGNAL(valueChanged(int)), m_signalMapper, SLOT(map()));

	ParameterSpinBox *MISC_COMPASS_KI = new ParameterSpinBox(Parameters::MISC_COMPASS_KI);
	m_parameterSpinBoxes.append(MISC_COMPASS_KI);
	miscBoxLayout->addRow(tr("COMPASS_KI:"), MISC_COMPASS_KI);
	m_signalMapper->setMapping(MISC_COMPASS_KI, MISC_COMPASS_KI);
	connect(MISC_COMPASS_KI, SIGNAL(valueChanged(int)), m_signalMapper, SLOT(map()));

	ParameterSpinBox *MISC_IDLE_SPEED = new ParameterSpinBox(Parameters::MISC_IDLE_SPEED);
	m_parameterSpinBoxes.append(MISC_IDLE_SPEED);
	miscBoxLayout->addRow(tr("IDLE_SPEED:"), MISC_IDLE_SPEED);
	m_signalMapper->setMapping(MISC_IDLE_SPEED, MISC_IDLE_SPEED);
	connect(MISC_IDLE_SPEED, SIGNAL(valueChanged(int)), m_signalMapper, SLOT(map()));

	ParameterSpinBox *MISC_SKIP_CONTROL_CYCLES = new ParameterSpinBox(Parameters::MISC_SKIP_CONTROL_CYCLES);
	m_parameterSpinBoxes.append(MISC_SKIP_CONTROL_CYCLES);
	miscBoxLayout->addRow(tr("SKIP_CONTROL_CYCLES:"), MISC_SKIP_CONTROL_CYCLES);
	m_signalMapper->setMapping(MISC_SKIP_CONTROL_CYCLES, MISC_SKIP_CONTROL_CYCLES);
	connect(MISC_SKIP_CONTROL_CYCLES, SIGNAL(valueChanged(int)), m_signalMapper, SLOT(map()));

	ParameterSpinBox *MISC_START_THRESHOLD = new ParameterSpinBox(Parameters::MISC_START_THRESHOLD);
	m_parameterSpinBoxes.append(MISC_START_THRESHOLD);
	miscBoxLayout->addRow(tr("START_THRESHOLD:"), MISC_START_THRESHOLD);
	m_signalMapper->setMapping(MISC_START_THRESHOLD, MISC_START_THRESHOLD);
	connect(MISC_START_THRESHOLD, SIGNAL(valueChanged(int)), m_signalMapper, SLOT(map()));

	ParameterSpinBox *MISC_STOP_THRESHOLD = new ParameterSpinBox(Parameters::MISC_STOP_THRESHOLD);
	m_parameterSpinBoxes.append(MISC_STOP_THRESHOLD);
	miscBoxLayout->addRow(tr("STOP_THRESHOLD:"), MISC_STOP_THRESHOLD);
	m_signalMapper->setMapping(MISC_STOP_THRESHOLD, MISC_STOP_THRESHOLD);
	connect(MISC_STOP_THRESHOLD, SIGNAL(valueChanged(int)), m_signalMapper, SLOT(map()));

	QGroupBox *pitchBox = new QGroupBox(tr("PITCH"));
	QFormLayout *pitchBoxLayout = new QFormLayout();
	pitchBox->setLayout(pitchBoxLayout);

	ParameterSpinBox *PITCH_AVERAGINGFILTER = new ParameterSpinBox(Parameters::PITCH_AVERAGINGFILTER);
	m_parameterSpinBoxes.append(PITCH_AVERAGINGFILTER);
	pitchBoxLayout->addRow(tr("AVERAGINGFILTER:"), PITCH_AVERAGINGFILTER);
	m_signalMapper->setMapping(PITCH_AVERAGINGFILTER, PITCH_AVERAGINGFILTER);
	connect(PITCH_AVERAGINGFILTER, SIGNAL(valueChanged(int)), m_signalMapper, SLOT(map()));

	ParameterSpinBox *PITCH_ILIMIT = new ParameterSpinBox(Parameters::PITCH_ILIMIT);
	m_parameterSpinBoxes.append(PITCH_ILIMIT);
	pitchBoxLayout->addRow(tr("ILIMIT:"), PITCH_ILIMIT);
	m_signalMapper->setMapping(PITCH_ILIMIT, PITCH_ILIMIT);
	connect(PITCH_ILIMIT, SIGNAL(valueChanged(int)), m_signalMapper, SLOT(map()));

	ParameterSpinBox *PITCH_KD = new ParameterSpinBox(Parameters::PITCH_KD);
	m_parameterSpinBoxes.append(PITCH_KD);
	pitchBoxLayout->addRow(tr("KD:"), PITCH_KD);
	m_signalMapper->setMapping(PITCH_KD, PITCH_KD);
	connect(PITCH_KD, SIGNAL(valueChanged(int)), m_signalMapper, SLOT(map()));

	ParameterSpinBox *PITCH_KI = new ParameterSpinBox(Parameters::PITCH_KI);
	m_parameterSpinBoxes.append(PITCH_KI);
	pitchBoxLayout->addRow(tr("KI:"), PITCH_KI);
	m_signalMapper->setMapping(PITCH_KI, PITCH_KI);
	connect(PITCH_KI, SIGNAL(valueChanged(int)), m_signalMapper, SLOT(map()));

	ParameterSpinBox *PITCH_KP = new ParameterSpinBox(Parameters::PITCH_KP);
	m_parameterSpinBoxes.append(PITCH_KP);
	pitchBoxLayout->addRow(tr("KP:"), PITCH_KP);
	m_signalMapper->setMapping(PITCH_KP, PITCH_KP);
	connect(PITCH_KP, SIGNAL(valueChanged(int)), m_signalMapper, SLOT(map()));

	ParameterSpinBox *PITCH_RESOLUTIONFILTER = new ParameterSpinBox(Parameters::PITCH_RESOLUTIONFILTER);
	m_parameterSpinBoxes.append(PITCH_RESOLUTIONFILTER);
	pitchBoxLayout->addRow(tr("RESOLUTIONFILTER:"), PITCH_RESOLUTIONFILTER);
	m_signalMapper->setMapping(PITCH_RESOLUTIONFILTER, PITCH_RESOLUTIONFILTER);
	connect(PITCH_RESOLUTIONFILTER, SIGNAL(valueChanged(int)), m_signalMapper, SLOT(map()));

	QGroupBox *rollBox = new QGroupBox(tr("ROLL"));
	QFormLayout *rollBoxLayout = new QFormLayout();
	rollBox->setLayout(rollBoxLayout);

	ParameterSpinBox *ROLL_AVERAGINGFILTER = new ParameterSpinBox(Parameters::ROLL_AVERAGINGFILTER);
	m_parameterSpinBoxes.append(ROLL_AVERAGINGFILTER);
	rollBoxLayout->addRow(tr("AVERAGINGFILTER:"), ROLL_AVERAGINGFILTER);
	m_signalMapper->setMapping(ROLL_AVERAGINGFILTER, ROLL_AVERAGINGFILTER);
	connect(ROLL_AVERAGINGFILTER, SIGNAL(valueChanged(int)), m_signalMapper, SLOT(map()));

	ParameterSpinBox *ROLL_ILIMIT = new ParameterSpinBox(Parameters::ROLL_ILIMIT);
	m_parameterSpinBoxes.append(ROLL_ILIMIT);
	rollBoxLayout->addRow(tr("ILIMIT:"), ROLL_ILIMIT);
	m_signalMapper->setMapping(ROLL_ILIMIT, ROLL_ILIMIT);
	connect(ROLL_ILIMIT, SIGNAL(valueChanged(int)), m_signalMapper, SLOT(map()));

	ParameterSpinBox *ROLL_KD = new ParameterSpinBox(Parameters::ROLL_KD);
	m_parameterSpinBoxes.append(ROLL_KD);
	rollBoxLayout->addRow(tr("KD:"), ROLL_KD);
	m_signalMapper->setMapping(ROLL_KD, ROLL_KD);
	connect(ROLL_KD, SIGNAL(valueChanged(int)), m_signalMapper, SLOT(map()));

	ParameterSpinBox *ROLL_KI = new ParameterSpinBox(Parameters::ROLL_KI);
	m_parameterSpinBoxes.append(ROLL_KI);
	rollBoxLayout->addRow(tr("KI:"), ROLL_KI);
	m_signalMapper->setMapping(ROLL_KI, ROLL_KI);
	connect(ROLL_KI, SIGNAL(valueChanged(int)), m_signalMapper, SLOT(map()));

	ParameterSpinBox *ROLL_KP = new ParameterSpinBox(Parameters::ROLL_KP);
	m_parameterSpinBoxes.append(ROLL_KP);
	rollBoxLayout->addRow(tr("KP:"), ROLL_KP);
	m_signalMapper->setMapping(ROLL_KP, ROLL_KP);
	connect(ROLL_KP, SIGNAL(valueChanged(int)), m_signalMapper, SLOT(map()));

	ParameterSpinBox *ROLL_RESOLUTIONFILTER = new ParameterSpinBox(Parameters::ROLL_RESOLUTIONFILTER);
	m_parameterSpinBoxes.append(ROLL_RESOLUTIONFILTER);
	rollBoxLayout->addRow(tr("RESOLUTIONFILTER:"), ROLL_RESOLUTIONFILTER);
	m_signalMapper->setMapping(ROLL_RESOLUTIONFILTER, ROLL_RESOLUTIONFILTER);
	connect(ROLL_RESOLUTIONFILTER, SIGNAL(valueChanged(int)), m_signalMapper, SLOT(map()));

	QGroupBox *yawBox = new QGroupBox(tr("YAW"));
	QFormLayout *yawBoxLayout = new QFormLayout();
	yawBox->setLayout(yawBoxLayout);

	ParameterSpinBox *YAW_AVERAGINGFILTER = new ParameterSpinBox(Parameters::YAW_AVERAGINGFILTER);
	m_parameterSpinBoxes.append(YAW_AVERAGINGFILTER);
	yawBoxLayout->addRow(tr("AVERAGINGFILTER:"), YAW_AVERAGINGFILTER);
	m_signalMapper->setMapping(YAW_AVERAGINGFILTER, YAW_AVERAGINGFILTER);
	connect(YAW_AVERAGINGFILTER, SIGNAL(valueChanged(int)), m_signalMapper, SLOT(map()));

	ParameterSpinBox *YAW_ILIMIT = new ParameterSpinBox(Parameters::YAW_ILIMIT);
	m_parameterSpinBoxes.append(YAW_ILIMIT);
	yawBoxLayout->addRow(tr("ILIMIT:"), YAW_ILIMIT);
	m_signalMapper->setMapping(YAW_ILIMIT, YAW_ILIMIT);
	connect(YAW_ILIMIT, SIGNAL(valueChanged(int)), m_signalMapper, SLOT(map()));

	ParameterSpinBox *YAW_KD = new ParameterSpinBox(Parameters::YAW_KD);
	m_parameterSpinBoxes.append(YAW_KD);
	yawBoxLayout->addRow(tr("KD:"), YAW_KD);
	m_signalMapper->setMapping(YAW_KD, YAW_KD);
	connect(YAW_KD, SIGNAL(valueChanged(int)), m_signalMapper, SLOT(map()));

	ParameterSpinBox *YAW_KI = new ParameterSpinBox(Parameters::YAW_KI);
	m_parameterSpinBoxes.append(YAW_KI);
	yawBoxLayout->addRow(tr("KI:"), YAW_KI);
	m_signalMapper->setMapping(YAW_KI, YAW_KI);
	connect(YAW_KI, SIGNAL(valueChanged(int)), m_signalMapper, SLOT(map()));

	ParameterSpinBox *YAW_KP = new ParameterSpinBox(Parameters::YAW_KP);
	m_parameterSpinBoxes.append(YAW_KP);
	yawBoxLayout->addRow(tr("KP:"), YAW_KP);
	m_signalMapper->setMapping(YAW_KP, YAW_KP);
	connect(YAW_KP, SIGNAL(valueChanged(int)), m_signalMapper, SLOT(map()));

	ParameterSpinBox *YAW_RESOLUTIONFILTER = new ParameterSpinBox(Parameters::YAW_RESOLUTIONFILTER);
	m_parameterSpinBoxes.append(YAW_RESOLUTIONFILTER);
	yawBoxLayout->addRow(tr("RESOLUTIONFILTER:"), YAW_RESOLUTIONFILTER);
	m_signalMapper->setMapping(YAW_RESOLUTIONFILTER, YAW_RESOLUTIONFILTER);
	connect(YAW_RESOLUTIONFILTER, SIGNAL(valueChanged(int)), m_signalMapper, SLOT(map()));

	parameterGroupsLayout->addWidget(miscBox);
	parameterGroupsLayout->addWidget(pitchBox);
	parameterGroupsLayout->addWidget(rollBox);
	parameterGroupsLayout->addWidget(yawBox);

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
	foreach (ParameterSpinBox *le, m_parameterSpinBoxes)
	{
		auto msg = QSharedPointer<GetParameterMessage>(new GetParameterMessage(le->parameterTypeId()));
		auto proxymsg = QSharedPointer<ProxyMessage>(new ProxyMessage());
		proxymsg->setInnerMessage(msg);
		m_mainWindow->enqueueMessage(proxymsg);
	}
}

void ParametersWidget::sendParameters()
{
	QSettings settings;

	foreach (ParameterSpinBox *le, m_parameterSpinBoxes)
	{
		auto msg = QSharedPointer<SetParameterMessage>(new SetParameterMessage(le->parameterTypeId(), le->value()));
		auto proxymsg = QSharedPointer<ProxyMessage>(new ProxyMessage());
		proxymsg->setInnerMessage(msg);
		m_mainWindow->enqueueMessage(proxymsg);

		settings.setValue(QString("parameters/%1").arg(ParameterTypeIdToString(le->parameterTypeId())), le->value());
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
			foreach (ParameterSpinBox *le, m_parameterSpinBoxes)
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

		foreach (ParameterSpinBox *le, m_parameterSpinBoxes)
		{
			le->setDisabled(readOnly);
			le->blockSignals(true);
			le->setValue(0);
			le->blockSignals(false);
		}

		if (profile.startsWith("{"))
		{
			QUuid profileUuid = QUuid(profile);
			if (profileUuid.isNull()) return;

			m_settings->beginGroup(profileUuid.toString());
			m_settings->beginGroup("parameters");
			foreach (ParameterSpinBox *le, m_parameterSpinBoxes)
			{
				le->blockSignals(true);
				le->setValue(m_settings->value(ParameterTypeIdToString(le->parameterTypeId())).toInt());
				le->blockSignals(false);
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

void ParametersWidget::setParameterSpinBoxValue(int parameterTypeId, int newValue, bool dontSetDirty)
{
	foreach (ParameterSpinBox *le, m_parameterSpinBoxes)
	{
		if (le->parameterTypeId() == parameterTypeId)
		{
			le->setValue(newValue);
			if (!dontSetDirty)
				setDirty(true);
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
		foreach (ParameterSpinBox *le, m_parameterSpinBoxes)
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
	// Brauch ich bestimmt irgendwann mal :|
	//ParameterSpinBox *parameterSpinBox = qobject_cast<ParameterSpinBox*>(widget);
	setDirty(true);
}

bool ParametersWidget::isDirty()
{
	return m_dirty;
}
