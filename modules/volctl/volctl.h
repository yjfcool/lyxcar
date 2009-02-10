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

#ifndef __VOLCTL_H__
#define __VOLCTL_H__

#include <QtGui>
#include <QPushButton>

#include "../../panel.h"
#include "../../buttons.h"
#include "../../m_interface.h"

class volCtlModuleApplet : public QWidget {
	Q_OBJECT
	public:
		/* public members */		
		volCtlModuleApplet(QWidget *parent = 0);
		~volCtlModuleApplet();

	private:
		/* private members */
		ALyxButton *vol_up_button;
		ALyxButton *vol_down_button;
		ALyxButton *vol_mute_button;
};

class volCtlModule : public QObject, M_Interface {
	Q_OBJECT
	Q_INTERFACES(M_Interface)

	public:
		void activate(QWidget *parent = 0);
		void activatePeriodically(QWidget *parent = 0) {}
		void appendToPanel(APanel *panel = 0, int position = 0);

	private:
		volCtlModuleApplet *appletWidget;
};


#endif
