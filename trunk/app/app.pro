TEMPLATE			= app
HEADERS				= ../main.h ../mainwindow.h ../mainmenu.h ../panel.h
SOURCES				= ../main.cpp ../mainwindow.cpp ../mainmenu.cpp ../panel.cpp
CONFIG				+= release config qt
QT				+= network xml sql
INCLUDEPATH			+= ./include
LIBS				+= -L../ -llyxlib
OBJECTS_DIR			= ./libs
MOC_DIR				= ./libs
TARGET				= lyxcar

win32:release {
	RC_FILE		= ../lyxcar.rc
	CONFIG		+= console
	DESTDIR		= ../
} 
