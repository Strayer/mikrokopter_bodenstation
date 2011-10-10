#include "parameterswidget.h"
#include "helper_functions.h"
#include "messages/all_messages.h"
#include "messages/parameter_type_ids.h"

#include <QtGui>
#include <QSharedPointer>

ParametersWidget::ParametersWidget(MainWindow *mainWindow, QWidget *parent) :
	QWidget(parent), m_mainWindow(mainWindow)
{
	QHBoxLayout *parameterGroupsLayout = new QHBoxLayout(parent);
	this->settings = new QSettings(qApp->applicationDirPath().append("/parameter_profiles.ini"), QSettings::IniFormat);

	QGroupBox *miscBox = new QGroupBox(tr("MISC"));
	QFormLayout *miscBoxLayout = new QFormLayout();
	miscBox->setLayout(miscBoxLayout);

	ParameterSpinBox *MISC_ACC_HORIZ_KI = new ParameterSpinBox(Parameters::MISC_ACC_HORIZ_KI);
	m_parameterSpinBoxes.append(MISC_ACC_HORIZ_KI);
	miscBoxLayout->addRow(tr("ACC_HORIZ_KI:"), MISC_ACC_HORIZ_KI);

	ParameterSpinBox *MISC_ACC_RANGE = new ParameterSpinBox(Parameters::MISC_ACC_RANGE);
	m_parameterSpinBoxes.append(MISC_ACC_RANGE);
	miscBoxLayout->addRow(tr("ACC_RANGE:"), MISC_ACC_RANGE);

	ParameterSpinBox *MISC_ACC_VERT_KI = new ParameterSpinBox(Parameters::MISC_ACC_VERT_KI);
	m_parameterSpinBoxes.append(MISC_ACC_VERT_KI);
	miscBoxLayout->addRow(tr("ACC_VERT_KI:"), MISC_ACC_VERT_KI);

	ParameterSpinBox *MISC_COMPASS_KI = new ParameterSpinBox(Parameters::MISC_COMPASS_KI);
	m_parameterSpinBoxes.append(MISC_COMPASS_KI);
	miscBoxLayout->addRow(tr("COMPASS_KI:"), MISC_COMPASS_KI);

	ParameterSpinBox *MISC_IDLE_SPEED = new ParameterSpinBox(Parameters::MISC_IDLE_SPEED);
	m_parameterSpinBoxes.append(MISC_IDLE_SPEED);
	miscBoxLayout->addRow(tr("IDLE_SPEED:"), MISC_IDLE_SPEED);

	ParameterSpinBox *MISC_SKIP_CONTROL_CYCLES = new ParameterSpinBox(Parameters::MISC_SKIP_CONTROL_CYCLES);
	m_parameterSpinBoxes.append(MISC_SKIP_CONTROL_CYCLES);
	miscBoxLayout->addRow(tr("SKIP_CONTROL_CYCLES:"), MISC_SKIP_CONTROL_CYCLES);

	ParameterSpinBox *MISC_START_THRESHOLD = new ParameterSpinBox(Parameters::MISC_START_THRESHOLD);
	m_parameterSpinBoxes.append(MISC_START_THRESHOLD);
	miscBoxLayout->addRow(tr("START_THRESHOLD:"), MISC_START_THRESHOLD);

	ParameterSpinBox *MISC_STOP_THRESHOLD = new ParameterSpinBox(Parameters::MISC_STOP_THRESHOLD);
	m_parameterSpinBoxes.append(MISC_STOP_THRESHOLD);
	miscBoxLayout->addRow(tr("STOP_THRESHOLD:"), MISC_STOP_THRESHOLD);

	QGroupBox *pitchBox = new QGroupBox(tr("PITCH"));
	QFormLayout *pitchBoxLayout = new QFormLayout();
	pitchBox->setLayout(pitchBoxLayout);

	ParameterSpinBox *PITCH_AVERAGINGFILTER = new ParameterSpinBox(Parameters::PITCH_AVERAGINGFILTER);
	m_parameterSpinBoxes.append(PITCH_AVERAGINGFILTER);
	pitchBoxLayout->addRow(tr("AVERAGINGFILTER:"), PITCH_AVERAGINGFILTER);

	ParameterSpinBox *PITCH_ILIMIT = new ParameterSpinBox(Parameters::PITCH_ILIMIT);
	m_parameterSpinBoxes.append(PITCH_ILIMIT);
	pitchBoxLayout->addRow(tr("ILIMIT:"), PITCH_ILIMIT);

	ParameterSpinBox *PITCH_KD = new ParameterSpinBox(Parameters::PITCH_KD);
	m_parameterSpinBoxes.append(PITCH_KD);
	pitchBoxLayout->addRow(tr("KD:"), PITCH_KD);

	ParameterSpinBox *PITCH_KI = new ParameterSpinBox(Parameters::PITCH_KI);
	m_parameterSpinBoxes.append(PITCH_KI);
	pitchBoxLayout->addRow(tr("KI:"), PITCH_KI);

	ParameterSpinBox *PITCH_KP = new ParameterSpinBox(Parameters::PITCH_KP);
	m_parameterSpinBoxes.append(PITCH_KP);
	pitchBoxLayout->addRow(tr("KP:"), PITCH_KP);

	ParameterSpinBox *PITCH_RESOLUTIONFILTER = new ParameterSpinBox(Parameters::PITCH_RESOLUTIONFILTER);
	m_parameterSpinBoxes.append(PITCH_RESOLUTIONFILTER);
	pitchBoxLayout->addRow(tr("RESOLUTIONFILTER:"), PITCH_RESOLUTIONFILTER);

	QGroupBox *rollBox = new QGroupBox(tr("ROLL"));
	QFormLayout *rollBoxLayout = new QFormLayout();
	rollBox->setLayout(rollBoxLayout);

	ParameterSpinBox *ROLL_AVERAGINGFILTER = new ParameterSpinBox(Parameters::ROLL_AVERAGINGFILTER);
	m_parameterSpinBoxes.append(ROLL_AVERAGINGFILTER);
	rollBoxLayout->addRow(tr("AVERAGINGFILTER:"), ROLL_AVERAGINGFILTER);

	ParameterSpinBox *ROLL_ILIMIT = new ParameterSpinBox(Parameters::ROLL_ILIMIT);
	m_parameterSpinBoxes.append(ROLL_ILIMIT);
	rollBoxLayout->addRow(tr("ILIMIT:"), ROLL_ILIMIT);

	ParameterSpinBox *ROLL_KD = new ParameterSpinBox(Parameters::ROLL_KD);
	m_parameterSpinBoxes.append(ROLL_KD);
	rollBoxLayout->addRow(tr("KD:"), ROLL_KD);

	ParameterSpinBox *ROLL_KI = new ParameterSpinBox(Parameters::ROLL_KI);
	m_parameterSpinBoxes.append(ROLL_KI);
	rollBoxLayout->addRow(tr("KI:"), ROLL_KI);

	ParameterSpinBox *ROLL_KP = new ParameterSpinBox(Parameters::ROLL_KP);
	m_parameterSpinBoxes.append(ROLL_KP);
	rollBoxLayout->addRow(tr("KP:"), ROLL_KP);

	ParameterSpinBox *ROLL_RESOLUTIONFILTER = new ParameterSpinBox(Parameters::ROLL_RESOLUTIONFILTER);
	m_parameterSpinBoxes.append(ROLL_RESOLUTIONFILTER);
	rollBoxLayout->addRow(tr("RESOLUTIONFILTER:"), ROLL_RESOLUTIONFILTER);

	QGroupBox *yawBox = new QGroupBox(tr("YAW"));
	QFormLayout *yawBoxLayout = new QFormLayout();
	yawBox->setLayout(yawBoxLayout);

	ParameterSpinBox *YAW_AVERAGINGFILTER = new ParameterSpinBox(Parameters::YAW_AVERAGINGFILTER);
	m_parameterSpinBoxes.append(YAW_AVERAGINGFILTER);
	yawBoxLayout->addRow(tr("AVERAGINGFILTER:"), YAW_AVERAGINGFILTER);

	ParameterSpinBox *YAW_ILIMIT = new ParameterSpinBox(Parameters::YAW_ILIMIT);
	m_parameterSpinBoxes.append(YAW_ILIMIT);
	yawBoxLayout->addRow(tr("ILIMIT:"), YAW_ILIMIT);

	ParameterSpinBox *YAW_KD = new ParameterSpinBox(Parameters::YAW_KD);
	m_parameterSpinBoxes.append(YAW_KD);
	yawBoxLayout->addRow(tr("KD:"), YAW_KD);

	ParameterSpinBox *YAW_KI = new ParameterSpinBox(Parameters::YAW_KI);
	m_parameterSpinBoxes.append(YAW_KI);
	yawBoxLayout->addRow(tr("KI:"), YAW_KI);

	ParameterSpinBox *YAW_KP = new ParameterSpinBox(Parameters::YAW_KP);
	m_parameterSpinBoxes.append(YAW_KP);
	yawBoxLayout->addRow(tr("KP:"), YAW_KP);

	ParameterSpinBox *YAW_RESOLUTIONFILTER = new ParameterSpinBox(Parameters::YAW_RESOLUTIONFILTER);
	m_parameterSpinBoxes.append(YAW_RESOLUTIONFILTER);
	yawBoxLayout->addRow(tr("RESOLUTIONFILTER:"), YAW_RESOLUTIONFILTER);

	parameterGroupsLayout->addWidget(miscBox);
	parameterGroupsLayout->addWidget(pitchBox);
	parameterGroupsLayout->addWidget(rollBox);
	parameterGroupsLayout->addWidget(yawBox);

	// Buttons

	profileButton = new QToolButton();
	profileButton->setArrowType(Qt::DownArrow);
	profileButton->setMenu(new QMenu());
	profileButton->setPopupMode(QToolButton::MenuButtonPopup);
	profileButton->setToolButtonStyle(Qt::ToolButtonTextOnly);

	QPushButton *getParametersButton = new QPushButton(tr("Parameter abfragen"));
	sendParametersButton = new QPushButton(tr("Parameter senden"));

	QHBoxLayout *buttonLayout = new QHBoxLayout();
	buttonLayout->addStretch();
	buttonLayout->addWidget(profileButton);
	buttonLayout->addWidget(getParametersButton);
	buttonLayout->addWidget(sendParametersButton);

	connect(profileButton, SIGNAL(triggered(QAction*)), this, SLOT(changeProfile(QAction*)));
	connect(profileButton, SIGNAL(clicked()), this, SLOT(saveProfile()));
	connect(getParametersButton, SIGNAL(clicked()), this, SLOT(getParameters()));
	connect(sendParametersButton, SIGNAL(clicked()), this, SLOT(sendParameters()));

	// Hauptlayout

	QVBoxLayout *mainLayout = new QVBoxLayout();
	mainLayout->addLayout(parameterGroupsLayout);
	mainLayout->addLayout(buttonLayout);
	setLayout(mainLayout);

	rebuildProfileMenu();
	changeProfile(profileButton->menu()->defaultAction());
}

ParametersWidget::~ParametersWidget()
{
	delete settings;
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

	if (profile == "new_profile")
	{
		bool ok;
		QString text = QInputDialog::getText(this, tr("Neues Profil"), tr("Name:"), QLineEdit::Normal, "", &ok);

		if (ok && !text.isEmpty())
		{
			QUuid profileUuid = QUuid::createUuid();

			settings->beginGroup(profileUuid.toString());
			settings->setValue("profileName", text);

			settings->beginGroup("parameters");
			foreach (ParameterSpinBox *le, m_parameterSpinBoxes)
				settings->setValue(ParameterTypeIdToString(le->parameterTypeId()), le->value());
			settings->endGroup();

			settings->endGroup();

			rebuildProfileMenu();

			// Action finden und auswählen
			foreach (QAction *action, profileButton->menu()->actions())
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
		profileButton->setText(QString("%1: %2").arg(tr("Profil")).arg(action->text()));
		bool readOnly = (profile == "read_only");
		activeProfile = profile;

		sendParametersButton->setDisabled(readOnly);

		foreach (ParameterSpinBox *le, m_parameterSpinBoxes)
		{
			le->setDisabled(readOnly);
			le->setValue(0);
		}

		if (profile.startsWith("{"))
		{
			QUuid profileUuid = QUuid(profile);
			if (profileUuid.isNull()) return;

			settings->beginGroup(profileUuid.toString());
			settings->beginGroup("parameters");
			foreach (ParameterSpinBox *le, m_parameterSpinBoxes)
				le->setValue(settings->value(ParameterTypeIdToString(le->parameterTypeId())).toInt());
			settings->endGroup();
			settings->endGroup();
		}
	}
}

void ParametersWidget::rebuildProfileMenu()
{
	QMenu *profileButtonMenu = profileButton->menu();
	profileButtonMenu->clear();

	QAction *readOnlyAction = new QAction(tr("Read-only"), profileButtonMenu);
	readOnlyAction->setData("read_only");
	profileButtonMenu->addAction(readOnlyAction);
	profileButtonMenu->addSeparator();

	foreach (QString le, settings->childGroups())
	{
		QAction *action = new QAction(settings->value(QString("%1/%2").arg(le).arg("profileName")).toString(), profileButtonMenu);
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
	foreach (ParameterSpinBox *le, m_parameterSpinBoxes)
	{
		if (le->parameterTypeId() == parameterTypeId)
			le->setValue(newValue);
	}
}

void ParametersWidget::saveProfile()
{
	if (activeProfile.startsWith("{"))
	{
		settings->beginGroup(activeProfile);
		settings->beginGroup("parameters");
		foreach (ParameterSpinBox *le, m_parameterSpinBoxes)
			settings->setValue(ParameterTypeIdToString(le->parameterTypeId()), le->value());
		settings->endGroup();
		settings->endGroup();
	}
}
