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

#ifndef __SCROLLBAR_H__
#define __SCROLLBAR_H__

#include <QWidget>
#include <QPixmap>

#include "skinner.h"
#include "buttons.h"

class ALyxScrollBar : public QWidget {
	Q_OBJECT
	public:
		ALyxScrollBar(QWidget *parent = 0, ASkinner *s = 0);
		~ALyxScrollBar();

	private:
		ASkinner *m_skinner;
		
		QPixmap backbtn_up;
		QPixmap backbtn_down;
		QPixmap forwardbtn_up;
		QPixmap forwardbtn_down;
		QPixmap slider_up;
		QPixmap slider_down;
		QPixmap bar_begin;
		QPixmap bar_end;
		QPixmap bar_fill;

		
	signals:
		void changed();

	protected:
		void paintEvent(QPaintEvent *e);
		void mousePressEvent(QMouseEvent *e);
};

#endif
