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

#include <QWidget>
#include <QLabel>
#include <QBoxLayout>
#include <QPalette>
#include <QBrush>
#include <QScrollArea>
#include <QToolButton>

#include <QDir>
#include <QFile>
#include <QRegExp>

#ifndef __AMAINMENU_H__
#define __AMAINMENU_H__

class AMainMenuButton : public QLabel {
	Q_OBJECT
	public:
		AMainMenuButton(QWidget *parent = 0);
		~AMainMenuButton() {}

	protected:
		void mousePressEvent(QMouseEvent *ev);
		void mouseReleaseEvent(QMouseEvent *ev);

	private:
		QList<QPixmap> buttonImages;

	signals:
		void activated();
};

class AMainMenuWidget : public QWidget {
 	Q_OBJECT
	public:
		AMainMenuWidget(QWidget *parent = 0);
		~AMainMenuWidget() {};
};

/*
 * Main menu class
 */


#endif
