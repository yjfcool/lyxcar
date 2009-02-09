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

#ifndef __MODULE_H__
#define __MODULE_H__

#include "../../m_interface.h"

class templateModule : public QObject, M_Interface {
	Q_OBJECT
	Q_INTERFACES(M_Interface)

	public:
		void activate(QWidget *parent = 0);
		void activatePeriodically(QWidget *parent = 0);
		void appendToPanel(APanel *panel = 0, int position = 0);
};

class templateModuleApplet : public QWidget {
	Q_OBJECT
	public:
		/* public members */		
		templateModuleApplet(QWidget *parent = 0);
		~templateModuleApplet();

	private:
		/* private members */
};

#endif
