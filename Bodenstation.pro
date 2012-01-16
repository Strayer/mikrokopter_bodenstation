QT += core gui opengl

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
	messages/parameter_type_ids.h \
	messages/proxymessage.h \
#    widgets/camerawidget.h \
	messages/cleartosendmessage.h \
	messages/decimaldebugdumpmessage.h \
	decimaldebughandler.h \
	widgets/parametercontrolwidget.h

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
	messages/curparametermessage.cpp \
	messages/proxymessage.cpp \
#    widgets/camerawidget.cpp \
	messages/cleartosendmessage.cpp \
	messages/decimaldebugdumpmessage.cpp \
	decimaldebughandler.cpp \
	widgets/parametercontrolwidget.cpp

FORMS += \
	serialportdialog.ui

LIBS+= -lwinspool

DEFINES += _WIN32_WINNT=0x0501

INCLUDEPATH+= E:/dev/lib/msvc_x86/boost-1.48.0/include# \
#	E:/dev/lib/msvc_x86_64/opencv-svn/include
LIBS+= -LE:/dev/lib/msvc_x86/boost-1.48.0/lib \
#	-LE:/dev/lib/msvc_x86_64/opencv-svn/lib \
#	-lopencv_highgui229 \
#	-lopencv_core229

RESOURCES += \
	resources.qrc

RC_FILE = icon.rc








