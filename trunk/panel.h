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

class APanel : public QWidget {
	Q_OBJECT
	public:
		APanel(QWidget *parent = 0, ASkinner *s = 0);
		~APanel();

		void fill();

		QWidget *infoBar;
		AMainMenuButton *button;
		AMainMenuWidget *widget;

		QScrollArea *scroller;
		QList<QToolButton *> items;

		QHBoxLayout *layout;

	protected:
		ASkinner * skinner;

	signals:
		void repaintModuleArea();

	public slots:
		void popup();
};

#endif
