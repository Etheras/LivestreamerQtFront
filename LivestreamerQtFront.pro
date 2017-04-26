#-------------------------------------------------
#
# Project created by QtCreator 2014-11-21T18:15:01
#
#-------------------------------------------------

QT += widgets network
CONFIG += release
CONFIG -= debug

RC_ICONS += appicon.ico
ICON += appicon.icns

TARGET  = LivestreamerQtFront
TEMPLATE = app

SOURCES += main.cpp \
	GUI/window.cpp \
	GUI/options.cpp \
	GUI/about.cpp

HEADERS += \
	Classes/networkmanager.hpp \
	Classes/channellabel.hpp \
	Classes/channelpage.hpp \
	Classes/navigationbutton.hpp \
        Classes/OpenStreamAction.hpp \
        Classes/OpenChatAction.hpp \
	GenericFunctions/genericfunctions.hpp \
	GenericFunctions/populate.hpp \
	GenericFunctions/clear.hpp \
	GenericFunctions/checkconfiguration.hpp \
	GenericFunctions/runlivestreamer.hpp \
        GenericFunctions/errorhandling.hpp \
	GenericVariables/genericvariables.hpp \
	GenericVariables/application.hpp \
	GenericVariables/path.hpp \
	GenericVariables/request.hpp \
	GenericVariables/security.hpp \
	GUI/window.hpp \
	GUI/options.hpp \
        GUI/about.hpp

FORMS   += \
	GUI/window.ui \
	GUI/options.ui \
	GUI/about.ui

RESOURCES +=

DISTFILES += \
    appicon.ico \
    appresource.rc
