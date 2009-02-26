TEMPLATE	= lib
CONFIG		+= plugin release
FORMS		= main.ui
HEADERS		= mp3player.h mplayerprocess.h
SOURCES		= mp3player.cpp mplayerprocess.cpp
TARGET		= mp3player
QT		+= xml
OBJECTS_DIR	= ./libs
MOC_DIR		= ./libs

win32:release {
	DESTDIR		= ./
}
