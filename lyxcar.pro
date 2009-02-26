TEMPLATE			= app
HEADERS				= main.h mainwindow.h mainmenu.h panel.h buttons.h osd.h skinner.h lists.h home.h scrollbar.h control.h m_interface.h
SOURCES				= main.cpp mainwindow.cpp mainmenu.cpp panel.cpp buttons.cpp osd.cpp skinner.cpp lists.cpp home.cpp scrollbar.cpp control.cpp
#TRANSLATIONS	= translate/ru.ts
CONFIG				+= release config qt
QT						+= network xml sql
INCLUDEPATH		+= ./include
LIBS					+= -L./release
OBJECTS_DIR	= ./libs
MOC_DIR		= ./libs


SUBDIRS		= modules/volctl

win32:release {
	RC_FILE		= lyxcar.rc
	CONFIG		+= console
	DESTDIR		= ./
} 
