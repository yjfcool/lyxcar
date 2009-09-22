TEMPLATE	= lib
CONFIG		+= plugin release
HEADERS		= playlistmgr.h
SOURCES		= playlistmgr.cpp
TARGET		= playlistmgr
QT		+= xml
INCLUDEPATH	+= ../../ ../ ../../lyxlib
LIBS		+= -L../.. -llyxlib
OBJECTS_DIR	= ./libs
MOC_DIR		= ./libs

win32:release {
	DESTDIR		= ./
}
