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

#ifndef __XINE_MOD_H__
#define __XINE_MOD_H__

#include <QtGui>
#include <QBoxLayout>

#include "../../m_interface.h"

class phononModule : public QObject, M_Interface {
	Q_OBJECT
	Q_INTERFACES(M_Interface)

	public:
		QWidget * activate(QWidget *parent = 0);
		QWidget * activateApplet(QWidget *parent = 0);
};

class phononWindow : public QWidget {
	Q_OBJECT
	public:
		phononWindow(QWidget *parent = 0);

	private:
};

#endif
