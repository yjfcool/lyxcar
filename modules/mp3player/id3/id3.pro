TEMPLATE=lib
SOURCES=id3.c md5.c tagpuller.c
CONFIG		+= release
TARGET		= id3
INCLUDEPATH	+= ../.. ../ ../../lyxlib
QT		+= xml
OBJECTS_DIR	= ./libs
MOC_DIR		= ./libs
DESTDIR		= ../

win32:release {
	SOURCES += mmap.c
}
