TEMPLATE	= lib
HEADERS		= ../animated.h ../display.h ../osd.h ../lists.h \
		  ../buttons.h ../control.h ../skinner.h ../scrollbar.h
SOURCES		= ../animated.cpp ../display.cpp ../osd.cpp ../lists.cpp \
		  ../buttons.cpp ../control.cpp ../skinner.cpp ../scrollbar.cpp
CONFIG		+= release
QT		+= xml sql
OBJECTS_DIR	= ./libs
MOC_DIR		= ./libs

win32:release {
	CONFIG		+= console
	DESTDIR		= ../
} 
