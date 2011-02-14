QT += core

HEADERS += \
	mainwindow.h \
	serialportdialog.h \
	enumser.h \
	SerialPort.h \
    serialportdevice.h

SOURCES += \
	main.cpp \
	mainwindow.cpp \
	serialportdialog.cpp \
	enumser.cpp \
	SerialPort.cpp \
    serialportdevice.cpp

FORMS += \
	serialportdialog.ui

LIBS+= -lwinspool

INCLUDEPATH+= E:/Entwicklung/lib/msvc_x86_64/boost-1.45.0/include
LIBS+= -LE:/Entwicklung/lib/msvc_x86_64/boost-1.45.0/lib
