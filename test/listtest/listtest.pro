TEMPLATE		= app
HEADERS			= listtest.h ../../skinner.h ../../lists.h ../../scrollbar.h
SOURCES			= listtest.cpp ../../skinner.cpp ../../lists.cpp ../../scrollbar.cpp
CONFIG			+= release config qt
QT			+= network xml sql
INCLUDEPATH		+= ./include
LIBS					+= -L../../ -llyxlib
OBJECTS_DIR	= ./libs
MOC_DIR		= ./libs
DESTDIR		= ../../
TARGET		= lt


win32:release {
	CONFIG		+= console
	DESTDIR		= ../
} 
