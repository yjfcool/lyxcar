TEMPLATE	= lib
CONFIG		+= plugin release
HEADERS		= mp3player.h mplayerprocess.h
SOURCES		= mp3player.cpp mplayerprocess.cpp
TARGET		= mp3player
INCLUDEPATH	+= ../.. ../
LIBS		+= -L../.. -llyxlib
QT		+= xml
OBJECTS_DIR	= ./libs
MOC_DIR		= ./libs

win32:release {
	DESTDIR		= ./
}
