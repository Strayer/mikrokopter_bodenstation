#include <QApplication>
#include "mainwindow.h"

#include <QtCore/QSharedPointer>
#include <messages/basemessage.h>

Q_DECLARE_METATYPE(QSharedPointer<BaseMessage>);

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);

	a.setApplicationName("Bodenstation-Ork");
	a.setOrganizationName("Olle Orks");
	a.setOrganizationDomain("olle-orks.org");

	qRegisterMetaType< QSharedPointer<BaseMessage> >();

	MainWindow w;

	w.show();

	return a.exec();
}
