SOURCES=AudioOutput.cpp \
	Backend.cpp \ 
	Effect.cpp \
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
	MPlayerVideoWidget.h \
	MediaController.h \
	MediaObject.h \
	SeekStack.h \
	SinkNode.h \
	VideoWidget.h \
	WidgetNoPaintEvent.h

INCLUDEPATH=../..

OBJECTS_DIR	= ./libs
MOC_DIR		= ./libs

CONFIG += qt lib release plugin
TARGET = phonon_mplayer
DESTDIR=../../..
TEMPLATE = lib
