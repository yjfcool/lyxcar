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
		//! \brief Virtual destructor.
		virtual ~M_Interface() {}

		QWidget * moduleWindow;
		//! \brief Pure virtual method. This must be implemented as needed to display module's interface in main window.
		/*!
			Module's main widget isn't constructed after module's loaded. That's why you need to call activate() function
			to create it's contents and fuctionality. This function returns QWidget * object.

			\param parent specifies parent widget for module's widget.
		*/
		virtual QWidget * activate(QWidget * parent = 0) = 0;
		//! \brief Pure virtual method. This must be implemented as needed to append module's control to panel.
		/*!
			Constructs and returns small applet widget to insert into panel. You need to call this if you need to create
			applet widget with module's functionality.

			\param parent specifies the panel to insert the control.
		*/
		virtual QWidget * activateApplet(QWidget * parent = 0) = 0;

		//! \brief Sets the ASkinner object.
		void setSkinner(ASkinner *skinnerObj) { qDebug() << "Skinner object set!"; skinner = skinnerObj; }

		QString moduleName() { return m_moduleName; }
		void setModuleName(QString name) { m_moduleName = name; }

	protected:
		ASkinner *skinner;
		QString m_moduleName;
};

Q_DECLARE_INTERFACE(M_Interface, "com.trolltech.Lyxcar.M_Interface/1.0"); 

#endif
