#ifndef PARAMETERCONTROLWIDGET_H
#define PARAMETERCONTROLWIDGET_H

#include <QWidget>

class QSpinBox;

class ParameterControlWidget : public QWidget
{
	Q_OBJECT
public:
	explicit ParameterControlWidget(int parameterTypeId, QWidget *parent = 0);

	int parameterTypeId();
	int value();

	void setReadOnly(bool toggle);
	void setValue(int value);
	void setDisabled(bool toggle);

	void contextMenuEvent(QContextMenuEvent *);

private:
	int m_parameterTypeId;
	int m_currentValue;
	bool m_readOnly;
	bool m_disabled;

	QSpinBox *m_spinBox;

private slots:
	void someEditingFinished();

signals:
	void valueChanged(int newValue);
	void editingFinished();

};

#endif // PARAMETERCONTROLWIDGET_H
