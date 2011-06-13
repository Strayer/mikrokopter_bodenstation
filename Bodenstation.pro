QT += core gui

HEADERS += \
	mainwindow.h \
	serialportdialog.h \
	enumser.h \
	SerialPort.h \
	serialporthandler.h \
	AsyncSerial.h \
    messages/basemessage.h \
    messages/pingmessage.h \
    helper_functions.h \
    messages/all_messages.h \
    messages/pongmessage.h \
    widgets/parameterswidget.h \
    messages/setparametermessage.h \
    messages/getparametermessage.h \
    messages/curparametermessage.h \
    messages/parameter_type_ids.h

SOURCES += \
	main.cpp \
	mainwindow.cpp \
	serialportdialog.cpp \
	enumser.cpp \
	SerialPort.cpp \
	serialporthandler.cpp \
	AsyncSerial.cpp \
    messages/basemessage.cpp \
    messages/pingmessage.cpp \
    helper_functions.cpp \
    messages/pongmessage.cpp \
    widgets/parameterswidget.cpp \
    messages/setparametermessage.cpp \
    messages/getparametermessage.cpp \
    messages/curparametermessage.cpp

FORMS += \
	serialportdialog.ui

LIBS+= -lwinspool

DEFINES += _WIN32_WINNT=0x0501

INCLUDEPATH+= E:/dev/lib/msvc_x86_64/boost-1.46.1/include
LIBS+= -LE:/dev/lib/msvc_x86_64/boost-1.46.1/lib

RESOURCES += \
    resources.qrc

RC_FILE = icon.rc
