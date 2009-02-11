/*
 * Copyright (C) 2008 Pavlov Denis
 *
 * Volume control module.
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
#include "../../skinner.h"
#include "../../m_interface.h"

class volCtlModuleApplet : public QWidget {
	Q_OBJECT
	public:
		/* public members */		
		volCtlModuleApplet(QWidget * parent = 0, ASkinner *s = 0);
		~volCtlModuleApplet();

		void setSkinner(ASkinner *s) { skinner = s; }

	private:
		/* private members */
		ALyxButton * vol_up_button;
		ALyxButton * vol_down_button;
		ALyxButton * vol_mute_button;

		ASkinner * skinner;

	private slots:
		void	volume_up();
		void	volume_down();
		void	volume_mute();
};

class volCtlModule : public QObject, M_Interface {
	Q_OBJECT
	Q_INTERFACES(M_Interface)

	public:

		/// @brief Module activation function.
		// Module activation stands for executing its code
		// in main area of an interface window.
		//
		void activate(QWidget * parent = 0);
		void activatePeriodically(QWidget * parent = 0) {}

		/// @brief Adding an applet to panel into specified position.
		//
		void appendToPanel(APanel * panel = 0, int position = 0);

	private:
		volCtlModuleApplet * appletWidget;
};


#endif
