TEMPLATE	= lib
CONFIG		+= plugin release
HEADERS		= volctl.h
SOURCES		= volctl.cpp
TARGET		= volctl
QT		+= xml
LIBS		+= -L../.. -llyxlib
OBJECTS_DIR	= ./libs
MOC_DIR		= ./libs

win32:release {
	DESTDIR		= ./
}
