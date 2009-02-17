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
//! \brief Picture buttons for LyxCar interface.
/*!
	Inherited from QAbstractButton. Generates Qt signals clicked(), doubleClicked(), pressed(), released() and so on.
*/
class ALyxButton : public QAbstractButton {
	Q_OBJECT
	public:
		//! \brief Constructs a button.
		/*!
			\param parent specifies parent widget for the button.
		*/
		ALyxButton(QWidget *parent = 0);
		
		//! \brief Sets released or unchecked button picture.
		/*!
			\param image is a QPixmap containing image.
		*/
		void setUpPixmap(QPixmap image);
		//! \brief Sets pressed or checked button picture.
		/*!
			\param image is a QPixmap containing image.
		*/
		void setDownPixmap(QPixmap image);

	private:
		bool currentState; // Button isn't pressed

		QPixmap buttonUpImage;
		QPixmap buttonDownImage;

		void mousePressEvent(QMouseEvent *e);
		void mouseReleaseEvent(QMouseEvent *e);
		
		void paintEvent(QPaintEvent *event);
	
	protected:

	signals:
		void clicked();
		void pressed();
		void released();
};

#endif
