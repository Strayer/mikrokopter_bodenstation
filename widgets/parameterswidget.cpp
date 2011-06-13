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
	QSettings settings;

	QGroupBox *miscBox = new QGroupBox(tr("MISC"));
	QFormLayout *miscBoxLayout = new QFormLayout();
	miscBox->setLayout(miscBoxLayout);

	ParameterSpinBox *MISC_ACC_HORIZ_KI = new ParameterSpinBox(Parameters::MISC_ACC_HORIZ_KI);
	m_parameterSpinBoxes.append(MISC_ACC_HORIZ_KI);
	MISC_ACC_HORIZ_KI->setValue(settings.value("parameters/MISC_ACC_HORIZ_KI", 0).toInt());
	miscBoxLayout->addRow(tr("ACC_HORIZ_KI:"), MISC_ACC_HORIZ_KI);

	ParameterSpinBox *MISC_ACC_VERT_KI = new ParameterSpinBox(Parameters::MISC_ACC_VERT_KI);
	m_parameterSpinBoxes.append(MISC_ACC_VERT_KI);
	MISC_ACC_VERT_KI->setValue(settings.value("parameters/MISC_ACC_VERT_KI", 0).toInt());
	miscBoxLayout->addRow(tr("ACC_VERT_KI:"), MISC_ACC_VERT_KI);

	ParameterSpinBox *MISC_COMPASS_KI = new ParameterSpinBox(Parameters::MISC_COMPASS_KI);
	m_parameterSpinBoxes.append(MISC_COMPASS_KI);
	MISC_COMPASS_KI->setValue(settings.value("parameters/MISC_COMPASS_KI", 0).toInt());
	miscBoxLayout->addRow(tr("COMPASS_KI:"), MISC_COMPASS_KI);

	ParameterSpinBox *MISC_IDLE_SPEED = new ParameterSpinBox(Parameters::MISC_IDLE_SPEED);
	m_parameterSpinBoxes.append(MISC_IDLE_SPEED);
	MISC_IDLE_SPEED->setValue(settings.value("parameters/MISC_IDLE_SPEED", 0).toInt());
	miscBoxLayout->addRow(tr("IDLE_SPEED:"), MISC_IDLE_SPEED);

	ParameterSpinBox *MISC_SKIP_CONTROL_CYCLES = new ParameterSpinBox(Parameters::MISC_SKIP_CONTROL_CYCLES);
	m_parameterSpinBoxes.append(MISC_SKIP_CONTROL_CYCLES);
	MISC_SKIP_CONTROL_CYCLES->setValue(settings.value("parameters/MISC_SKIP_CONTROL_CYCLES", 0).toInt());
	miscBoxLayout->addRow(tr("SKIP_CONTROL_CYCLES:"), MISC_SKIP_CONTROL_CYCLES);

	ParameterSpinBox *MISC_START_THRESHOLD = new ParameterSpinBox(Parameters::MISC_START_THRESHOLD);
	m_parameterSpinBoxes.append(MISC_START_THRESHOLD);
	MISC_START_THRESHOLD->setValue(settings.value("parameters/MISC_START_THRESHOLD", 0).toInt());
	miscBoxLayout->addRow(tr("START_THRESHOLD:"), MISC_START_THRESHOLD);

	ParameterSpinBox *MISC_STOP_THRESHOLD = new ParameterSpinBox(Parameters::MISC_STOP_THRESHOLD);
	m_parameterSpinBoxes.append(MISC_STOP_THRESHOLD);
	MISC_STOP_THRESHOLD->setValue(settings.value("parameters/MISC_STOP_THRESHOLD", 0).toInt());
	miscBoxLayout->addRow(tr("STOP_THRESHOLD:"), MISC_STOP_THRESHOLD);

	QGroupBox *pitchBox = new QGroupBox(tr("PITCH"));
	QFormLayout *pitchBoxLayout = new QFormLayout();
	pitchBox->setLayout(pitchBoxLayout);

	ParameterSpinBox *PITCH_AVERAGINGFILTER = new ParameterSpinBox(Parameters::PITCH_AVERAGINGFILTER);
	m_parameterSpinBoxes.append(PITCH_AVERAGINGFILTER);
	PITCH_AVERAGINGFILTER->setValue(settings.value("parameters/PITCH_AVERAGINGFILTER", 0).toInt());
	pitchBoxLayout->addRow(tr("AVERAGINGFILTER:"), PITCH_AVERAGINGFILTER);

	ParameterSpinBox *PITCH_ILIMIT = new ParameterSpinBox(Parameters::PITCH_ILIMIT);
	m_parameterSpinBoxes.append(PITCH_ILIMIT);
	PITCH_ILIMIT->setValue(settings.value("parameters/PITCH_ILIMIT", 0).toInt());
	pitchBoxLayout->addRow(tr("ILIMIT:"), PITCH_ILIMIT);

	ParameterSpinBox *PITCH_KD = new ParameterSpinBox(Parameters::PITCH_KD);
	m_parameterSpinBoxes.append(PITCH_KD);
	PITCH_KD->setValue(settings.value("parameters/PITCH_KD", 0).toInt());
	pitchBoxLayout->addRow(tr("KD:"), PITCH_KD);

	ParameterSpinBox *PITCH_KI = new ParameterSpinBox(Parameters::PITCH_KI);
	m_parameterSpinBoxes.append(PITCH_KI);
	PITCH_KI->setValue(settings.value("parameters/PITCH_KI", 0).toInt());
	pitchBoxLayout->addRow(tr("KI:"), PITCH_KI);

	ParameterSpinBox *PITCH_KP = new ParameterSpinBox(Parameters::PITCH_KP);
	m_parameterSpinBoxes.append(PITCH_KP);
	PITCH_KP->setValue(settings.value("parameters/PITCH_KP", 0).toInt());
	pitchBoxLayout->addRow(tr("KP:"), PITCH_KP);

	ParameterSpinBox *PITCH_RESOLUTIONFILTER = new ParameterSpinBox(Parameters::PITCH_RESOLUTIONFILTER);
	m_parameterSpinBoxes.append(PITCH_RESOLUTIONFILTER);
	PITCH_RESOLUTIONFILTER->setValue(settings.value("parameters/PITCH_RESOLUTIONFILTER", 0).toInt());
	pitchBoxLayout->addRow(tr("RESOLUTIONFILTER:"), PITCH_RESOLUTIONFILTER);

	QGroupBox *rollBox = new QGroupBox(tr("ROLL"));
	QFormLayout *rollBoxLayout = new QFormLayout();
	rollBox->setLayout(rollBoxLayout);

	ParameterSpinBox *ROLL_AVERAGINGFILTER = new ParameterSpinBox(Parameters::ROLL_AVERAGINGFILTER);
	m_parameterSpinBoxes.append(ROLL_AVERAGINGFILTER);
	ROLL_AVERAGINGFILTER->setValue(settings.value("parameters/ROLL_AVERAGINGFILTER", 0).toInt());
	rollBoxLayout->addRow(tr("AVERAGINGFILTER:"), ROLL_AVERAGINGFILTER);

	ParameterSpinBox *ROLL_ILIMIT = new ParameterSpinBox(Parameters::ROLL_ILIMIT);
	m_parameterSpinBoxes.append(ROLL_ILIMIT);
	ROLL_ILIMIT->setValue(settings.value("parameters/ROLL_ILIMIT", 0).toInt());
	rollBoxLayout->addRow(tr("ILIMIT:"), ROLL_ILIMIT);

	ParameterSpinBox *ROLL_KD = new ParameterSpinBox(Parameters::ROLL_KD);
	m_parameterSpinBoxes.append(ROLL_KD);
	ROLL_KD->setValue(settings.value("parameters/ROLL_KD", 0).toInt());
	rollBoxLayout->addRow(tr("KD:"), ROLL_KD);

	ParameterSpinBox *ROLL_KI = new ParameterSpinBox(Parameters::ROLL_KI);
	m_parameterSpinBoxes.append(ROLL_KI);
	ROLL_KI->setValue(settings.value("parameters/ROLL_KI", 0).toInt());
	rollBoxLayout->addRow(tr("KI:"), ROLL_KI);

	ParameterSpinBox *ROLL_KP = new ParameterSpinBox(Parameters::ROLL_KP);
	m_parameterSpinBoxes.append(ROLL_KP);
	ROLL_KP->setValue(settings.value("parameters/ROLL_KP", 0).toInt());
	rollBoxLayout->addRow(tr("KP:"), ROLL_KP);

	ParameterSpinBox *ROLL_RESOLUTIONFILTER = new ParameterSpinBox(Parameters::ROLL_RESOLUTIONFILTER);
	m_parameterSpinBoxes.append(ROLL_RESOLUTIONFILTER);
	ROLL_RESOLUTIONFILTER->setValue(settings.value("parameters/ROLL_RESOLUTIONFILTER", 0).toInt());
	rollBoxLayout->addRow(tr("RESOLUTIONFILTER:"), ROLL_RESOLUTIONFILTER);

	QGroupBox *yawBox = new QGroupBox(tr("YAW"));
	QFormLayout *yawBoxLayout = new QFormLayout();
	yawBox->setLayout(yawBoxLayout);

	ParameterSpinBox *YAW_AVERAGINGFILTER = new ParameterSpinBox(Parameters::YAW_AVERAGINGFILTER);
	m_parameterSpinBoxes.append(YAW_AVERAGINGFILTER);
	YAW_AVERAGINGFILTER->setValue(settings.value("parameters/YAW_AVERAGINGFILTER", 0).toInt());
	yawBoxLayout->addRow(tr("AVERAGINGFILTER:"), YAW_AVERAGINGFILTER);

	ParameterSpinBox *YAW_ILIMIT = new ParameterSpinBox(Parameters::YAW_ILIMIT);
	m_parameterSpinBoxes.append(YAW_ILIMIT);
	YAW_ILIMIT->setValue(settings.value("parameters/YAW_ILIMIT", 0).toInt());
	yawBoxLayout->addRow(tr("ILIMIT:"), YAW_ILIMIT);

	ParameterSpinBox *YAW_KD = new ParameterSpinBox(Parameters::YAW_KD);
	m_parameterSpinBoxes.append(YAW_KD);
	YAW_KD->setValue(settings.value("parameters/YAW_KD", 0).toInt());
	yawBoxLayout->addRow(tr("KD:"), YAW_KD);

	ParameterSpinBox *YAW_KI = new ParameterSpinBox(Parameters::YAW_KI);
	m_parameterSpinBoxes.append(YAW_KI);
	YAW_KI->setValue(settings.value("parameters/YAW_KI", 0).toInt());
	yawBoxLayout->addRow(tr("KI:"), YAW_KI);

	ParameterSpinBox *YAW_KP = new ParameterSpinBox(Parameters::YAW_KP);
	m_parameterSpinBoxes.append(YAW_KP);
	YAW_KP->setValue(settings.value("parameters/YAW_KP", 0).toInt());
	yawBoxLayout->addRow(tr("KP:"), YAW_KP);

	ParameterSpinBox *YAW_RESOLUTIONFILTER = new ParameterSpinBox(Parameters::YAW_RESOLUTIONFILTER);
	m_parameterSpinBoxes.append(YAW_RESOLUTIONFILTER);
	YAW_RESOLUTIONFILTER->setValue(settings.value("parameters/YAW_RESOLUTIONFILTER", 0).toInt());
	yawBoxLayout->addRow(tr("RESOLUTIONFILTER:"), YAW_RESOLUTIONFILTER);

	parameterGroupsLayout->addWidget(miscBox);
	parameterGroupsLayout->addWidget(pitchBox);
	parameterGroupsLayout->addWidget(rollBox);
	parameterGroupsLayout->addWidget(yawBox);

	QHBoxLayout *buttonLayout = new QHBoxLayout();
	QPushButton *getParametersButton = new QPushButton(tr("Parameter abfragen"));
	QPushButton *sendParametersButton = new QPushButton(tr("Parameter senden"));
	buttonLayout->addStretch();
	buttonLayout->addWidget(getParametersButton);
	buttonLayout->addWidget(sendParametersButton);
	connect(getParametersButton, SIGNAL(clicked()), this, SLOT(getParameters()));
	connect(sendParametersButton, SIGNAL(clicked()), this, SLOT(sendParameters()));

	QVBoxLayout *mainLayout = new QVBoxLayout();
	mainLayout->addLayout(parameterGroupsLayout);
	mainLayout->addLayout(buttonLayout);
	setLayout(mainLayout);
}

void ParametersWidget::getParameters()
{
	foreach (ParameterSpinBox *le, m_parameterSpinBoxes)
	{
		auto msg = QSharedPointer<GetParameterMessage>(new GetParameterMessage(le->parameterTypeId()));
		m_mainWindow->enqueueMessage(msg);
	}
}

void ParametersWidget::sendParameters()
{
	QSettings settings;

	foreach (ParameterSpinBox *le, m_parameterSpinBoxes)
	{
		auto msg = QSharedPointer<SetParameterMessage>(new SetParameterMessage(le->parameterTypeId(), le->value()));
		m_mainWindow->enqueueMessage(msg);

		settings.setValue(QString("parameters/%1").arg(ParameterTypeIdToString(le->parameterTypeId())), le->value());
	}
}
