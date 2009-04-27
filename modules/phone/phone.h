/*
 * Copyright (C) 2008-2009 Pavlov Denis
 *
 * Comments unavailable.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or any later version.
 *
*/

#ifndef __PHONE_H__
#define __PHONE_H__

#include <QWidget>
#include <QObject>
#include <QProcess>
#include <QSettings>
#include <QTextCodec>

#include "m_interface.h"

class phoneModule : public QObject, public M_Interface {
	Q_OBJECT
	Q_INTERFACES(M_Interface)

	public:
		QWidget * activate(QWidget *parent = 0);
		QWidget * activateApplet(QWidget *parent = 0);
		void deactivate(QString deactivateFor = "");

	signals:
		void demandActivation(QString moduleName);
		void deactivated(QString deactivateFor);
};


#endif
