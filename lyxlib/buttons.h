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
#include <QTimer>
#include <QtXml>

#include "control.h"
#include "skinner.h"

//! \brief Picture buttons for LyxCar interface.
/*!
	Inherited from QAbstractButton. Generates Qt signals clicked(), doubleClicked(), pressed(), released() and so on.
*/
class ALyxButton : public ALyxControl {
	Q_OBJECT
	public:
		//! \brief Constructs a button.
		/*!
			\param parent specifies parent widget for the button.
		*/
        	ALyxButton(QWidget *parent = 0);

		~ALyxButton();
		
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

		//! \brief Configures button according to skin settings.
		/*!
			\param s is a skinner object
			\param moduleName is a section of skin definition XML file containing the configuration of a module
			\param buttonName is a name of a button
		*/
		void setSkin(ASkinner *s, QString moduleName, QString buttonName);

	private:
		QTimer *animationTimer;
		int animationStep; // 1 - forward, -1 backward, 0 stop
		double currentOpacity; // 0.0 - 1.0

		bool currentState; // Button isn't pressed

		QPixmap buttonUpImage;
		QPixmap buttonDownImage;

		void mousePressEvent(QMouseEvent *e);
		void mouseReleaseEvent(QMouseEvent *e);
		void resizeEvent(QResizeEvent *e);

	protected:
		void paintEvent(QPaintEvent *event);
	
	private slots:
		void animate(); // Animation frame step

	protected:

	signals:
		//! \brief Emits this signal when user press and then releases mouse button.
		void clicked();
		//! \brief Emits this signal when user press mouse button.
		void pressed();
		//! \brief Emits this signal when user releases pressed mouse button.
		void released();
};

class ALyxPushButton : public ALyxButton {
	Q_OBJECT
	public:
		ALyxPushButton(QWidget *parent = 0, QString text = "");
		~ALyxPushButton();

		void setText(QString text);
		QString text() { return m_text; }

	private:
		QString m_text;

		void paintEvent(QPaintEvent *e);
};

#endif

