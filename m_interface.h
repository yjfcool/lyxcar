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

#ifndef __M_INTERFACE_H__
#define __M_INTERFACE_H__

#include <QWidget>
#include <QtPlugin>

#include "panel.h"
#include "skinner.h"

//! \brief This is a basic interface for implementing modules for LyxCar.

class M_Interface {
	public:
		QWidget * moduleWindow;
		//! \brief Pure virtual method. This must be implemented as needed to display module's interface in main window.
		/*!
			\param parent specifies parent widget for module's widget.
		*/
		virtual void activate(QWidget * parent = 0);
		virtual void activatePeriodically(QWidget * parent = 0);
		//! \brief Pure virtual method. This must be implemented as needed to append module's control to panel.
		/*!
			\param panel specifies the panel to insert the control.
			\param position specifies the position in which the control is inserted.
		*/
		virtual void appendToPanel(APanel * panel = 0, int position = 0);

		//! \brief Sets the ASkinner object.
		void setSkinner(ASkinner *skinnerObj) { printf("Skinner object set!\n"); skinner = skinnerObj; }

	protected:
		ASkinner *skinner;

};

Q_DECLARE_INTERFACE(M_Interface, "com.trolltech.Plugin.M_Interface/1.0"); 

#endif
