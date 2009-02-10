/*
 * Copyright (C) 2008 Pavlov Denis
 *
 * Comments unavailable.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or any later version.
 *
*/

#include "main.h"

int main(int argc, char * argv[]) {
	QApplication app(argc, argv);
	
//	if (!QSystemTrayIcon::isSystemTrayAvailable()) {
//		QMessageBox::critical(0, QObject::tr("Systray"), QObject::tr("I couldn't detect any system tray on this system."));
//		return 1;
//	}

//	QTranslator translator;
//	translator.load("../translate/ru.qm");
//	app.installTranslator(&translator);
	
//	Q_INIT_RESOURCE(docstyle);
	
	AMainWindow window((QWidget *)QApplication::desktop());
	window.show();

	return app.exec();
}
