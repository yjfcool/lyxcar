TEMPLATE	= lib
CONFIG		+= plugin release
HEADERS		= volctl.h
SOURCES		= volctl.cpp
TARGET		= volctl
QT		+= xml
INCLUDEPATH	+= ../.. ../ ../../3rdparty ../../lyxlib
LIBS		+= -L../.. -llyxlib -lphonon
OBJECTS_DIR	= ./libs
MOC_DIR		= ./libs

win32:release {
	DESTDIR		= ./
}
