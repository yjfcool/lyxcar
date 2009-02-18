TEMPLATE		= app
HEADERS			= listtest.h ../skinner.h ../lists.h
SOURCES			= listtest.cpp ../skinner.cpp ../lists.cpp
CONFIG			+= release config qt
QT			+= network xml sql
INCLUDEPATH		+= ./include
LIBS					+= -L./release
OBJECTS_DIR	= ./libs
MOC_DIR		= ./libs


win32:release {
	CONFIG		+= console
	DESTDIR		= ../
} 
