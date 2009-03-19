TEMPLATE = lib
CONFIG   += plugin
HEADERS  = clock.h
SOURCES  = clock.cpp
TARGET   = clock

QT += xml
INCLUDEPATH += ../../ ../../lyxlib
LIBS += -L../.. -llyxlib
