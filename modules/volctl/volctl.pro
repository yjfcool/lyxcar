TEMPLATE	= lib
CONFIG		+= plugin release
HEADERS		= volctl.h ../../buttons.h ../../skinner.h ../../control.h
SOURCES		= volctl.cpp ../../buttons.cpp ../../skinner.cpp ../../control.cpp
TARGET		= volctl
QT		+= xml
OBJECTS_DIR	= ./libs
MOC_DIR		= ./libs

win32:release {
	DESTDIR		= ./
}
