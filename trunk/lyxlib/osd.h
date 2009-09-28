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
#include <QTimer>
#include <QLabel>
#include <QBoxLayout>

#ifndef _OSD_H_
#define _OSD_H_

//! \brief This class implements on-screen-display for useful information, e.g. when changing volume or TV-channel.
class ALyxOSD : public QWidget {
	Q_OBJECT
	public:
		//! \brief Constructor, constructs OSD object.
		/*!
			\param parent specifies parent widget.
		*/
		ALyxOSD(QWidget *parent = 0);
		~ALyxOSD();
		
		QTimer	*showHideTimer;
		QLabel	*textLabel;
		QLabel	*pictureLabel;
		QVBoxLayout *mainLayout;
		
		void	show();
		void	showOnce();
		void	hide();
		void	setShowInterval(qint8 interval);
		void	setColor(QColor color);

		void	inform(QString text);
		void	setInfo(QPixmap image = QPixmap(), QString text = "");
		void	setPixmap(QPixmap image);
		void	setText(QString text);
};

#endif
