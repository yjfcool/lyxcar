SOURCES=AudioOutput.cpp \
	Backend.cpp \ 
	DeviceManager.cpp \
	Effect.cpp \
	EffectManager.cpp \
	MediaController.cpp \
	MediaObject.cpp \
	SeekStack.cpp \
	SinkNode.cpp \
	VLCMediaController.cpp \
	VLCMediaObject.cpp \
	VLCVideoWidget.cpp \
	VideoWidget.cpp \
	WidgetNoPaintEvent.cpp \
	vlc_loader.cpp

HEADERS=AudioOutput.h \
	Backend.h \ 
	DeviceManager.h \
	Effect.h \
	EffectManager.h \
	MediaController.h \
	MediaObject.h \
	SeekStack.h \
	SinkNode.h \
	VLCMediaController.cpp \
	VLCMediaObject.cpp \
	VLCVideoWidget.cpp \
	VideoWidget.h \
	WidgetNoPaintEvent.h \
	vlc_loader.h

INCLUDEPATH=../..

OBJECTS_DIR	= ./libs
MOC_DIR		= ./libs

CONFIG += qt lib release plugin
TARGET = phonon_vlc
DESTDIR=../../..
TEMPLATE = lib
