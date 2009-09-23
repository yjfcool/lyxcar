TEMPLATE			   = app
HEADERS				= ../main.h ../mainwindow.h ../mainmenu.h ../panel.h
SOURCES				= ../main.cpp ../mainwindow.cpp ../mainmenu.cpp ../panel.cpp
CONFIG				+= config qt release
QT				+= network xml sql
INCLUDEPATH			+= ./include ../lyxlib ../3rdparty
LIBS				+= -L../ -llyxlib -lphonon4
OBJECTS_DIR			= ./libs
MOC_DIR				= ./libs
TARGET				= lyxcar
DESTDIR				= ../

win32:release {
	RC_FILE		= ../lyxcar.rc
	CONFIG		+= console
} 
