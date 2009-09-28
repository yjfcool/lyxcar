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
unix { 
    # this feature will be work if pkg-config found tag.pc
    # (taglib should be installed in /usr/lib (may be in /usr/local/lib too)
    # CONFIG += link_pkgconfig
    # PKGCONFIG += tag
    LIBS += $$system(taglib-config --libs)
    QMAKE_CXXFLAGS += $$system(taglib-config --cflags)
}
win32:release {
	DESTDIR		= ./
        LIBS            += -llibtag
}
