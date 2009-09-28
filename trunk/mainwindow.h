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

#ifndef __MAINWINDOW_H__
#define __MAINWINDOW_H__

#include <QMainWindow>
#include <QSettings>

#include <QLabel>
#include <QBoxLayout>

#include "m_interface.h"
#include "skinner.h"
#include "buttons.h"
#include "osd.h"

//! \brief The class of main window.
/*!
 * 
 */
class AMainWindow : public QMainWindow {
		Q_OBJECT
	public:
	        //! Constructs main window
		explicit AMainWindow(QWidget * parent = 0);
	        AMainWindow(const QString & skinName, QWidget * parent = 0);

		//! Destructor
	        ~AMainWindow();

	        //! \brief Returns current active module name.
	        QString activeModuleName() { return m_activeModuleName; }

		ALyxOSD	*osd;

//		void	closeEvent(QCloseEvent *) {};

	private:
		void init(const QString & skin_name);

	public slots:
		//! \brief Activates a module named "moduleName". Activation means the module widget is inserted into main area and
		//! activeModuleName() is set to "moduleName".
		void activateModule(QString moduleName);

	private:

		QWidget *mainArea;	//! Area for viewing modules!
		APanel	*panel; // Panel object
		ASkinner *skinner; // Skin engine object

		QStringList modulesList;	// Module names list
		QHash<QString, QObject *> modules; // Module objects list by name

		QString m_activeModuleName;	// Contains name of module which is displayed in main area now
		M_Interface *m_interface;

		//! \brief Loads plugin with name <moduleName>. Returns true if there was an error.
		bool	loadModule(QString moduleName);

		void activateModuleDemand(QString moduleName);

		//! \brief Clears main area layout. NOTICE: Widgets inserted into that layout lose their parent, that's why we need
		//! to destroy them properly on application quit.
		void clearMainArea();

		bool fillPanel();

		//
		// Main audio output for the program used by every module!
		//
		Phonon::AudioOutput *m_audioOutput;

	private slots:
		void replyActivation(QString mname);
};


#endif
