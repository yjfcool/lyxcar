TEMPLATE = lib
CONFIG += plugin \
    qt \
    release
HEADERS = mp3player.h \
    playerdisplay.h \
    foldercontentsloader.h \
    database.h \
    playlist.h
SOURCES = mp3player.cpp \
    playerdisplay.cpp \
    foldercontentsloader.cpp \
    database.cpp \
    playlist.cpp
TARGET = mp3player
INCLUDEPATH += ../.. \
    ../ \
    ../../lyxlib \
    ../../3rdparty \
    ../../3rdparty/taglib
LIBS += -L../.. \
    -llyxlib
QT += xml \
    sql
OBJECTS_DIR = ./libs
MOC_DIR = ./libs
unix { 
    # this feature will be work if pkg-config found tag.pc
    # (taglib should be installed in /usr/lib (may be in /usr/local/lib too)
    # CONFIG += link_pkgconfig
    # PKGCONFIG += tag
    LIBS += $$system(taglib-config --libs)
    QMAKE_CXXFLAGS += $$system(taglib-config --cflags)
}
win32:release { 
    DESTDIR = ./
    INCLUDEPATH += ./taglib
    LIBS += -llibtag \
        -lphonon4
}
unix:LIBS += -lphonon
