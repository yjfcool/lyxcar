/*
 * Copyright (C) 2008 Pavlov Denis
 *
 * This is a skin engine implementation.
 * Engine is used by EVERY module to make it look like a main window
 * of an application.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or any later version.
 *
*/

#ifndef __SKINNER_H__
#define __SKINNER_H__

#include <QtXml>
#include <QtGui>
#include <QString>

class ASkinner {
	public:
		ASkinner();
		ASkinner(QString skinName);

		int loadSkin(QString name);

		QDomDocument * skin;
		QDomElement skinRoot;

	private:
		QString	skinsPath;
		QString skinName;
};

#endif
