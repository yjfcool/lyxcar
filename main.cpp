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
	
//	QTranslator translator;
//	translator.load("./translate/ru.qm");
//	app.installTranslator(&translator);
	
//	Q_INIT_RESOURCE(docstyle);

	qApp->setStyleSheet("QTreeWidget { border-style: outset;  border-width: 1px; border-radius: 10px; border-color: white; padding: 5px; background-color: white; \
	selection-background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #fbac8c, stop: 0.45 #fba756, stop:0.47 #fa9730, stop:1 #fed32e); show-decoration-selected: 1; font-size: 14pt; font-family: Calibri, Tahoma; \
	} \
	QScrollBar:horizontal { \
		height: 30px; \
     } \
  QScrollBar:vertical { \
		width: 30px; \
  } \
  QScrollBar::handle:vertical { \
		background-color: #bb0000; \
  } \
  QScrollBar::add-line:vertical { \
		height: 40px; \
  } \
  QScrollBar::sub-line { \
		width: 40px; \
  } ");
	
	AMainWindow window(qobject_cast<QWidget *>(QApplication::desktop()));
	window.show();

	return app.exec();
}
