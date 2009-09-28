TEMPLATE	= lib
CONFIG		+= plugin release
HEADERS		= playlistmgr.h ../mp3player/playlist.h
SOURCES		= playlistmgr.cpp ../mp3player/playlist.cpp
TARGET		= playlistmgr
QT		+= xml
INCLUDEPATH	+= ../../ ../ ../../lyxlib ../../3rdparty ../../3rdparty/taglib
LIBS		+= -L../.. -llyxlib
OBJECTS_DIR	= ./libs
MOC_DIR		= ./libs

win32:release {
	DESTDIR		= ./
        LIBS            += -llibtag
}
