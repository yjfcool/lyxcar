TEMPLATE	= lib
CONFIG		+= plugin release
HEADERS		= default_home.h
SOURCES		= default_home.cpp
TARGET		= default_home
QT		+= xml
LIBS		+= -L../.. -llyxlib
OBJECTS_DIR	= ./libs
MOC_DIR		= ./libs

win32:release {
	DESTDIR		= ./
}
