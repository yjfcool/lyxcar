TEMPLATE	= lib
CONFIG		+= plugin
HEADERS		= phonon_mod.h ../../buttons.h ../../skinner.h ../../control.h
SOURCES		= phonon_mod.cpp ../../buttons.cpp ../../skinner.cpp ../../control.cpp
TARGET		= phonon_mod
INCLUDEPATH	+= ../.. ../
QT		+= xml
OBJECTS_DIR	= ./libs
MOC_DIR		= ./libs

win32:release {
	DESTDIR		= ./
}
