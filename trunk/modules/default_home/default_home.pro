TEMPLATE	= lib
CONFIG		+= plugin release
HEADERS		= default_home.h ../../buttons.h ../../skinner.h
SOURCES		= default_home.cpp ../../buttons.cpp ../../skinner.cpp
TARGET		= default_home
QT		+= xml
OBJECTS_DIR	= ./libs
MOC_DIR		= ./libs

win32:release {
	DESTDIR		= ./
}
