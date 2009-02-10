TEMPLATE	= app
HEADERS         = main.h mainwindow.h mainmenu.h panel.h buttons.h osd.h \
		  skinner.h
SOURCES         = main.cpp mainwindow.cpp mainmenu.cpp panel.cpp buttons.cpp osd.cpp \
		  skinner.cpp
#TRANSLATIONS	= translate/ru.ts
CONFIG		+= release config qt
QT		+= network xml sql
INCLUDEPATH     += ./include
LIBS		+= -L./release


SUBDIRS		= modules/volctl

win32:release {
#	RC_FILE		= lyxcar.rc 
	CONFIG		+= console
	OBJECTS_DIR	= ./
	DESTDIR		= ./
} 
