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

int main(int argc, char * argv[])
{
	QApplication app(argc, argv);
	
//	QTranslator translator;
//	translator.load("./translate/ru.qm");
//	app.installTranslator(&translator);
	
//	Q_INIT_RESOURCE(docstyle);

   // TODO: change to normal args parser
   QString skin("default");
   for (int i = 0; i < argc; ++i)
   {
      if ((QString(argv[i]) == "-skin") && (i + 1 < argc))
      {
         skin = QString(argv[i + 1]);
         break;
      }
   }

	AMainWindow window(skin, qobject_cast<QWidget *>(QApplication::desktop()));
	window.show();

	return app.exec();
}
