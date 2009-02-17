TEMPLATE	= lib
CONFIG		+= plugin
HEADERS		= phonon_mod.h ../../buttons.h ../../skinner.h
SOURCES		= phonon_mod.cpp ../../buttons.cpp ../../skinner.cpp
TARGET		= phonon_mod
QT		+= xml

win32:release {
	DESTDIR		= ./
	OBJECTS_DIR	= ./libs
	MOC_DIR		= ./libs
}
