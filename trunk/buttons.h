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

#ifndef __BUTTONS_H__
#define __BUTTONS_H__

#include <QAbstractButton>
#include <QPixmap>
#include <QPainter>

class ALyxButton : public QAbstractButton {
	Q_OBJECT
	public:
		ALyxButton(QWidget *parent = 0);
		
		void setUpPixmap(QPixmap image);
		void setDownPixmap(QPixmap image);

	private:
		bool currentState; // Button isn't pressed

		QPixmap buttonUpImage;
		QPixmap buttonDownImage;

		void mousePressEvent(QMouseEvent *e);
		void mouseReleaseEvent(QMouseEvent *e);

	protected:
		void paintEvent(QPaintEvent *event);
};

#endif

