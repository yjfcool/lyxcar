TEMPLATE		= app
HEADERS			= listtest.h
SOURCES			= listtest.cpp
CONFIG			+= release config qt
QT			+= network xml sql
INCLUDEPATH		+= ./include
LIBS					+= -L../../ -llyxlib
OBJECTS_DIR	= ./libs
MOC_DIR		= ./libs
DESTDIR		= ../../
TARGET		= listtest


win32:release {
	CONFIG		+= console
} 
