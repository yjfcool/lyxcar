TEMPLATE	= lib
CONFIG		+= plugin release
FORMS		= main.ui
HEADERS		= mp3player.h mplayerprocess.h ../../skinner.h ../../buttons.h ../../control.h
SOURCES		= mp3player.cpp mplayerprocess.cpp ../../skinner.cpp ../../buttons.cpp ../../control.cpp
TARGET		= mp3player
QT		+= xml
OBJECTS_DIR	= ./libs
MOC_DIR		= ./libs

win32:release {
	DESTDIR		= ./
}
