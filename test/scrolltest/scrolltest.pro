TEMPLATE		= app
HEADERS			= scrolltest.h
SOURCES			= scrolltest.cpp
CONFIG			+= release config qt
QT			+= network xml sql
INCLUDEPATH		+= ./include
LIBS					+= -L../../ -llyxlib
OBJECTS_DIR	= ./libs
MOC_DIR		= ./libs
DESTDIR		= ../../
TARGET		= scrolltest


win32:release {
	CONFIG		+= console
} 
