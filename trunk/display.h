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

#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include "control.h"
#include "scrolllabel.h"
#include "buttons.h"

typedef QList<ALyxControl *> ALyxDisplayLayout;

//! \brief ALyxDisplay implements display widget which can contain
//! labels, icons, animations etc.
class ALyxDisplay : public ALyxControl {
	Q_OBJECT
	public:
		ALyxDisplay(QWidget *parent = 0);
		~ALyxDisplay();

		ALyxDisplayLayout getLayout(QString layoutName);

		void setBackgroundPixmap(QPixmap pixmap) { m_background = pixmap; repaint(); }

	private:
		QMap<QString, ALyxDisplayLayout> m_layouts;

		QPixmap m_background;

		void paintEvent(QPaintEvent *e);

	private slots:

	public slots:
		void activateLayout(QString layoutName);
};

#endif
