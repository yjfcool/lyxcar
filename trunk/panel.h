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

#ifndef __PANEL_H__
#define __PANEL_H__

#include "mainmenu.h"
#include "skinner.h"

//! Panel bar class
/*!
  This implements panel for inserting applets.
*/
class APanel : public QWidget {
	Q_OBJECT
	public:
		//! Constructor
		/*!
			\param parent is a parent widget
			\param s is an ASkinner object
		*/
		APanel(QWidget *parent = 0, ASkinner *s = 0);
		~APanel();

		void fill();

	protected:

	private:
		ASkinner * skinner;
		
		QWidget *infoBar;
		AMainMenuButton *button;
		AMainMenuWidget *widget;

		QScrollArea *scroller;
		QList<QToolButton *> items;

	signals:
		//! This signal is emitted when module rectangle needs to be redrawed.
		void repaintModuleArea();

	public slots:
		void popup();
};

#endif
