TEMPLATE		= app
HEADERS			= animtest.h
SOURCES			= animtest.cpp
CONFIG			+= release config qt
QT			+= xml
INCLUDEPATH		+= ./include
LIBS			+= -L../.. -llyxlib
OBJECTS_DIR	= ./libs
MOC_DIR		= ./libs
DESTDIR		= ../
TARGET		= at


win32:release {
	CONFIG		+= console
	DESTDIR		= ../
} 
