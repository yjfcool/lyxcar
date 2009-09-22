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

#include <phonon/audiooutput.h>
#include <phonon/mediaobject.h>

//! \brief This is a basic interface for implementing modules for LyxCar.

class M_Interface {
	public:
		//! \brief Virtual destructor.
		virtual ~M_Interface() {}

		QWidget * moduleWindow;
		//! \brief This must be implemented as needed to display module's interface in main window.
		/*!
			Module's main widget isn't constructed after module's loaded. That's why you need to call activate() function
			to create it's contents and fuctionality. This function returns QWidget * object.

			\param parent specifies parent widget for module's widget.
		*/
		virtual QWidget * activate(QWidget * parent = 0) = 0;

		//! \brief This must be implemented as needed to hide module's interface in main window.
		/*!
		    \param deactivateFor tells the module that it needs to be deactivated to allow another module take it's place
		    this parameter is used by main window to gt to know which module must be activated after.

			<b>ATTENTION: This method must emit deacivated(deactivateFor) to get main window to know
			that module widget deactivation procedure has been completed.

			That's why you need to declare signal deactivated(QString) in module implementation directly,
			because Qt interfaces mechanisms do not support declaring signals in module interfaces.</b>
		*/
		virtual void deactivate(QString deactivateFor = "") = 0;

		//! \brief Pure virtual method. This must be implemented as needed to append module's control to panel.
		/*!
			Constructs and returns small applet widget to insert into panel. You need to call this if you need to create
			applet widget with module's functionality.

			\param parent specifies the panel to insert the control.
		*/
		virtual QWidget * activateApplet(QWidget * parent = 0) = 0;

		//! \brief Sets the ASkinner object.
		void setSkinner(ASkinner *skinnerObj) { qDebug() << "Skinner object set!"; m_skinner = skinnerObj; }

		//! \brief Get module name
		QString moduleName() { return m_moduleName; }
		
		//! \brief Set module name
		void setModuleName(QString name) { m_moduleName = name; }
		
		//! \brief Set Phonon audio output interface for the module to make it possible to use it.
		//! The program has only one audio interface and every module use it for it's purposes.
		void setAudioOutput(Phonon::AudioOutput *output) { m_audioOutput = output; }

	protected:
		QString		m_moduleName;
		bool		closable; // If set, module is deleted during deactivation procedure, 
					  // otherwise it's just hidden.
		ASkinner	*m_skinner;
		Phonon::AudioOutput *m_audioOutput;
};

Q_DECLARE_INTERFACE(M_Interface, "com.trolltech.Lyxcar.M_Interface/1.0"); 

#endif
