TEMPLATE		= app
HEADERS			= animtest.h ../skinner.h ../lists.h ../scrollbar.h ../animated.h ../buttons.h ../control.h ../scrolllabel.h
SOURCES			= animtest.cpp ../skinner.cpp ../lists.cpp ../scrollbar.cpp ../animated.cpp ../buttons.cpp ../control.cpp ../scrolllabel.cpp
CONFIG			+= release config qt
QT			+= xml
INCLUDEPATH		+= ./include
LIBS			+= -L./release
OBJECTS_DIR	= ./libs
MOC_DIR		= ./libs
DESTDIR		= ../
TARGET		= at


win32:release {
	CONFIG		+= console
	DESTDIR		= ../
} 
