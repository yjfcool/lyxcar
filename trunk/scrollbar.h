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
		
		int m_position;
		int m_maximumPosition;
		
		int m_sliderOffset; // Current slider position in pixels
		int m_sliderStep;	// Slider one step (when pressing forward or backward button) in items
		int m_sliderPage; // Slider page step (when pressing on a slider bar above or below the slider) in items


		int tmp_sliderMin;
		int tmp_sliderLength;
		float tmp_sliderStep;
		
		bool tmp_sliderPressed;
		QPoint tmp_sliderPressPos;
		int tmp_sliderInitialPos;
		
	signals:
		void changed();

	protected:
		void resizeEvent(QResizeEvent *e);
		void paintEvent(QPaintEvent *e);

		void mousePressEvent(QMouseEvent *e);
		void mouseReleaseEvent(QMouseEvent *e);
		void mouseMoveEvent(QMouseEvent *e);
};

#endif
