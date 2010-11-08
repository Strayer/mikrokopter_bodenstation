QT += core

HEADERS += \
    mainwindow.h \
    serialportdialog.h \
    enumser.h \
    SerialPort.h

SOURCES += \
	main.cpp \
    mainwindow.cpp \
    serialportdialog.cpp \
    enumser.cpp \
    SerialPort.cpp

FORMS += \
    serialportdialog.ui

LIBS+= -lwinspool
