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

//! \brief Provided for convinience.
typedef QList<ALyxControl *> ALyxDisplayLayout;

//! \brief ALyxDisplay implements display widget which can contain
//! labels, icons, animations etc.
/*!
	ALyxDisplay is based on layouts. Display layout is a set of controls,
	labels etc. displayed at the same time. You may call it the page.

	Each layout has a name of QString. Display layout object itself is of 
	QList&lt;ALyxControl *&gt;.
*/
class ALyxDisplay : public ALyxControl {
	Q_OBJECT
	public:
		//! \brief Constructs display layout object.
		ALyxDisplay(QWidget *parent = 0);
		~ALyxDisplay();

		//! \brief Get named display layout of type ALyxDisplayLayout
		ALyxDisplayLayout displayLayout(QString layoutName);

		//! \brief Set display background pixmap
		void setBackgroundPixmap(QPixmap pixmap) { m_background = pixmap; repaint(); }

		void createLayout(QString layoutName);
		QStringList layouts();

		void insertWidget(QString layoutName, QWidget *widget);

	private:
		QMap<QString, ALyxDisplayLayout> m_layouts;

		QPixmap m_background;

		void paintEvent(QPaintEvent *e);

	private slots:

	public slots:
		//! \brief Shows specified layout.
		void activateLayout(QString layoutName);
};

#endif
