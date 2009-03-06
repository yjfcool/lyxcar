TEMPLATE		= app
HEADERS			= jogtest.h
SOURCES			= jogtest.cpp
CONFIG			+= release config qt
QT			+= xml
INCLUDEPATH		+= ./include ../../lyxlib ../..
LIBS			+= -L../.. -llyxlib
OBJECTS_DIR	= ./libs
MOC_DIR		= ./libs
DESTDIR		= ../../
TARGET		= jogtest


win32:release {
	CONFIG		+= console
} 
