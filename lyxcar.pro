TEMPLATE	= app
HEADERS         = main.h mainwindow.h mainmenu.h panel.h buttons.h
SOURCES         = main.cpp mainwindow.cpp mainmenu.cpp panel.cpp buttons.cpp
#RESOURCES       = docstyle.qrc
#FORMS		= 111.ui
#TRANSLATIONS	= translate/ru.ts
CONFIG		+= plugin release config qt
QT		+= network xml sql
INCLUDEPATH     += ./include
LIBS		+= -L./release

#RC_FILE		= docstyle.rc 
