#include "parametercontrolwidget.h"
#include "helper_functions.h"

#include <QtGui>

ParameterControlWidget::ParameterControlWidget(int parameterTypeId, QWidget *parent) :
	QWidget(parent), m_parameterTypeId(parameterTypeId), m_currentValue(0), m_readOnly(false)
{
	QLabel *label = new QLabel(this);
	label->setText(ParameterTypeIdToString(m_parameterTypeId).append(":"));

	m_spinBox = new QSpinBox(this);
	m_spinBox->setMinimum(INT_MIN); // Hier steht NICHT -2147483648 weil: http://bit.ly/uflXkq
	m_spinBox->setMaximum(2147483647);
	connect(m_spinBox, SIGNAL(editingFinished()), this, SLOT(someEditingFinished()));

	QHBoxLayout *layout = new QHBoxLayout(this);
	layout->addWidget(label);
	layout->addWidget(m_spinBox);

	setLayout(layout);
}

int ParameterControlWidget::parameterTypeId()
{
	return m_parameterTypeId;
}

void ParameterControlWidget::someEditingFinished()
{
	if (m_spinBox->value() != m_currentValue)
	{
		m_currentValue = m_spinBox->value();

		if (!m_readOnly && !m_disabled)
			emit editingFinished();
	}
}

int ParameterControlWidget::value()
{
	return m_currentValue;
}

void ParameterControlWidget::setValue(int value)
{
	m_currentValue = value;
	m_spinBox->blockSignals(true);
	m_spinBox->setValue(m_currentValue);
	m_spinBox->blockSignals(false);
}

void ParameterControlWidget::setReadOnly(bool toggle)
{
	m_readOnly = toggle;
	m_spinBox->setReadOnly(m_readOnly);
}

void ParameterControlWidget::setDisabled(bool toggle)
{
	m_disabled = toggle;
	m_spinBox->setDisabled(toggle);
}

void ParameterControlWidget::contextMenuEvent(QContextMenuEvent *event)
{
	QMenu contextMenu;

	QAction *bigNumbersWindowAction = new QAction(this);
	bigNumbersWindowAction->setText("Im \"Große Zahlen\"-Fenster anzeigen");
	contextMenu.addAction(bigNumbersWindowAction);

	QAction *selectedAction = contextMenu.exec(event->globalPos());

	if (selectedAction == bigNumbersWindowAction)
	{

	}

	bigNumbersWindowAction->deleteLater();
}
