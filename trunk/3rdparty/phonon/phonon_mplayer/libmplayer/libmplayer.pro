SOURCES=MPlayerLoader.cpp \
	MPlayerProcess.cpp \ 
	MPlayerVersion.cpp \
	MediaData.cpp \
	MediaSettings.cpp \
	MyProcess.cpp
	
HEADERS=MPlayerLoader.h \
	MPlayerProcess.h \ 
	MPlayerVersion.h \
	MediaData.h \
	MediaSettings.h \
	MyProcess.h

INCLUDEPATH=../../..

OBJECTS_DIR	= ./libs
MOC_DIR		= ./libs

CONFIG += qt lib release static
TARGET = mplayer
DESTDIR = ../../../..
TEMPLATE = lib
