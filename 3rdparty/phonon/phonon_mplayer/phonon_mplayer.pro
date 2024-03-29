SOURCES=AudioOutput.cpp \
	Backend.cpp \ 
	Effect.cpp \
	EffectManager.cpp \
	MPlayerVideoWidget.cpp \
	MediaController.cpp \
	MediaObject.cpp \
	SeekStack.cpp \
	SinkNode.cpp \
	VideoWidget.cpp \
	WidgetNoPaintEvent.cpp

HEADERS=AudioOutput.h \
	Backend.h \ 
	Effect.h \
	EffectManager.h \
	MPlayerVideoWidget.h \
	MediaController.h \
	MediaObject.h \
	SeekStack.h \
	SinkNode.h \
	VideoWidget.h \
	WidgetNoPaintEvent.h

INCLUDEPATH=../..

OBJECTS_DIR	= ./libs
MOC_DIR	= ./libs
LIBPATH+= ../../..
win32:release {
    LIBS += ../../../libmplayer.a -lphonon4
}

unix {
    LIBS += ../../../libmplayer.a -lphonon
}

CONFIG += qt lib release plugin
TARGET = phonon_mplayer
DESTDIR=../../../phonon_backend
TEMPLATE = lib
