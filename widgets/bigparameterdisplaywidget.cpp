#include "bigparameterdisplaywidget.h"

#include "messages/parameter_type_ids.h"
#include "helper_functions.h"

#include <QtGui>
#include <QtDebug>

BigParameterDisplayWidget::BigParameterDisplayWidget(SerialPortHandler *handler, QWidget *parent) :
	QWidget(parent)
{
	connect(handler, SIGNAL(newMessageReceived(QSharedPointer<BaseMessage>)), this, SLOT(newMessageReceived(QSharedPointer<BaseMessage>)));

	m_layout = new QVBoxLayout(this);
	setLayout(m_layout);

	setMinimumSize(400, 300);

	setAttribute(Qt::WA_DeleteOnClose);

	QTimer::singleShot(0, this, SLOT(showSetupWindow()));
}

BigParameterDisplayWidget::~BigParameterDisplayWidget()
{
}

void BigParameterDisplayWidget::newMessageReceived(QSharedPointer<BaseMessage> msg)
{
	if (msg->messageType() != BaseMessage::MessageTypes::CUR_PARAMETER)
		return;

	QSharedPointer<CurParameterMessage> curParameterMsg = msg.staticCast<CurParameterMessage>();

	if (m_typeIdToLabelHash.contains(curParameterMsg->parameterTypeId()))
		m_typeIdToLabelHash.value(curParameterMsg->parameterTypeId())
				->setText(QString("%1: %2").arg(ParameterTypeIdToString(curParameterMsg->parameterTypeId())).arg(curParameterMsg->value()));
}

void BigParameterDisplayWidget::showSetupWindow()
{
	QDialog *dlg = new QDialog(this);

	QGridLayout *layout = new QGridLayout(dlg);

	std::vector<int> parameterVector = Parameters::getParameterVector();
	QHash<int, QCheckBox*> checkboxHash;
	for (unsigned int i = 0; i < parameterVector.size(); i++)
	{
		QCheckBox *chkbox = new QCheckBox();
		chkbox->setText(ParameterTypeIdToString(parameterVector.at(i)));
		layout->addWidget(chkbox, i, 0);
		checkboxHash.insert(parameterVector.at(i), chkbox);
	}
	dlg->setLayout(layout);

	dlg->exec();

	// Momentane Labels löschen...
	QHash<int, QLabel*>::const_iterator iter;
	for (iter = m_typeIdToLabelHash.constBegin(); iter != m_typeIdToLabelHash.constEnd(); ++iter)
		iter.value()->deleteLater();
	m_typeIdToLabelHash.clear();

	// Neue Labels erstellen
	QHash<int, QCheckBox*>::const_iterator iter2;
	for (iter2 = checkboxHash.constBegin(); iter2 != checkboxHash.constEnd(); ++iter2)
	{
		if (!iter2.value()->isChecked())
			continue;
		QLabel *label = new QLabel(this);
		label->setText(QString("%1: ???").arg(ParameterTypeIdToString(iter2.key())));
		label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
		m_layout->addWidget(label);
		m_typeIdToLabelHash.insert(iter2.key(), label);
	}

	QTimer::singleShot(0, this, SLOT(fitLabelsToContent()));
}

void BigParameterDisplayWidget::fitLabelsToContent()
{
	QHash<int, QLabel*>::const_iterator iter;
	int fontSize = 12;
	QLabel *currLabel = NULL;
	int maxWidth = m_layout->contentsRect().width();
	QFont font("Monospace");
	font.setStyleHint(QFont::TypeWriter);

	for (iter = m_typeIdToLabelHash.constBegin(); iter != m_typeIdToLabelHash.constEnd(); ++iter)
	{
		currLabel = iter.value();
		font.setPointSize(12);

		while(true)
		{
			QFontMetrics fontMetrics(font);
			QRect rect = fontMetrics.boundingRect(QString("%1: 12345").arg(ParameterTypeIdToString(iter.key())));

			if (rect.width() < maxWidth && rect.height() < currLabel->height())
				font.setPointSize(font.pointSize()+1);
			else if (font.pointSize()-1 < fontSize || fontSize == 12)
			{
				fontSize = font.pointSize() - 1;
				break;
			}
			else
				break;
		}
	}

	font.setPointSize(fontSize);

	for (iter = m_typeIdToLabelHash.constBegin(); iter != m_typeIdToLabelHash.constEnd(); ++iter)
		iter.value()->setFont(font);
}

void BigParameterDisplayWidget::resizeEvent(QResizeEvent *event)
{
	fitLabelsToContent();
}
