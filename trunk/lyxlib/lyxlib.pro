TEMPLATE	= lib
HEADERS		= animated.h display.h osd.h lists.h \
		  buttons.h control.h skinner.h scrollbar.h \
		  scrolllabel.h dialogs.h devicesdlg.h jogdial.h
SOURCES		= animated.cpp display.cpp osd.cpp lists.cpp \
		  buttons.cpp control.cpp skinner.cpp scrollbar.cpp \
		  scrolllabel.cpp dialogs.cpp devicesdlg.cpp jogdial.cpp
CONFIG		+= qt release
QT		+= xml sql
OBJECTS_DIR	= ./libs
MOC_DIR		= ./libs
DESTDIR		= ../

win32:release {
	CONFIG		+= console
} 
