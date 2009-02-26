TEMPLATE	= lib
CONFIG		+= plugin release
HEADERS		= default_home.h ../../animated.h ../../buttons.h ../../skinner.h ../../control.h ../../m_interface.h
SOURCES		= default_home.cpp ../../animated.cpp ../../buttons.cpp ../../skinner.cpp ../../control.cpp
TARGET		= default_home
QT		+= xml
OBJECTS_DIR	= ./libs
MOC_DIR		= ./libs

win32:release {
	DESTDIR		= ./
}
