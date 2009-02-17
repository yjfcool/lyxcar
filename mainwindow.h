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

#ifndef __MAINWINDOW_H__
#define __MAINWINDOW_H__

#include <QMainWindow>
#include <QSettings>

#include <QLabel>
#include <QBoxLayout>

#include "m_interface.h"
#include "skinner.h"
#include "buttons.h"

//! \brief The class of main window.
/*!
 * 
 */
class AMainWindow : public QMainWindow {
		Q_OBJECT
	public:
		//! Constructs main window
		AMainWindow(QWidget *parent = 0);
		~AMainWindow();

//		void	closeEvent(QCloseEvent *) {};

	public slots:
		//! \brief Call this if you want to display home page.
		void goHome();

	private:
		ALyxButton *homeBtn;
		
		QWidget *mainArea;	//! Area for viewing modules!
		APanel	*panel; // Panel object
		ASkinner *skinner; // Skin engine object

		QStringList modulesList;	// Module names list
		QHash<QString, QObject *> modules; // Module objects list by name
		
		M_Interface *m_interface;
		
		//! \brief Loads plugin with name <moduleName>. Returns true if there was an error.
		bool	loadModule(QString moduleName);
		
		bool fillPanel();

	private slots:
};


#endif
