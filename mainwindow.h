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

/*
 * Main window class
 */

class AMainWindow : public QMainWindow {
		Q_OBJECT
	public:
		AMainWindow(QWidget *parent = 0);
		~AMainWindow();

		QWidget *mainArea;	// Area for viewing modules!
		APanel	*panel;
		ASkinner *skinner;

		void	closeEvent(QCloseEvent *) {};
		bool	loadPlugin();

		M_Interface *m_interface;

	private slots:
};


#endif
