TEMPLATE = lib
CONFIG += plugin \
    qt \
    release
HEADERS = phone.h phonewindow.h
SOURCES = phone.cpp phonewindow.cpp
TARGET = phone
INCLUDEPATH += ../.. \
    ../ \
    ../../lyxlib \
    ../../3rdparty
LIBS += -L../.. \
    -llyxlib -lphonon
QT += xml
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
    LIBS += -llibtag
}
