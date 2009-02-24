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

#include "scrollbar.h"

ALyxScrollBar::ALyxScrollBar(QWidget *parent, ASkinner *s) : QWidget(parent) {
	m_skinner = s;
	
	backbtn_up = QPixmap("./skins/default/list_up_btn.png");
	backbtn_down = QPixmap("./skins/default/list_up_btn.png");
	forwardbtn_up = QPixmap("./skins/default/list_dn_btn.png");
	forwardbtn_down = QPixmap("./skins/default/list_dn_btn.png");
	slider_up = QPixmap("./skins/default/scroller.png");
	slider_down = QPixmap("./skins/default/scroller.png");

	tmp_sliderPressed = false;
	
	m_position = 50;
	m_maximumPosition = 100;
	
	setAttribute(Qt::WA_NoSystemBackground, true);	
}

ALyxScrollBar::~ALyxScrollBar() {
	
}

void ALyxScrollBar::resizeEvent(QResizeEvent *e) {
	// Calculate slider button position
	tmp_sliderMin = backbtn_up.height();
	tmp_sliderLength = height()-forwardbtn_up.height()-tmp_sliderMin-backbtn_up.height();
	tmp_sliderStep = (float)tmp_sliderLength / (float)m_maximumPosition;
}

void ALyxScrollBar::paintEvent(QPaintEvent *e) {
	QPainter p(this);
	
	p.drawPixmap(0, 0, backbtn_up);
	p.drawPixmap(0, height()-forwardbtn_up.height(), forwardbtn_up);
	p.drawPixmap(0, tmp_sliderMin+(int)(tmp_sliderStep*m_position), slider_up);
	
	p.end();
}

void ALyxScrollBar::mousePressEvent(QMouseEvent *e) {
	if(QRect(0, 0, backbtn_up.width(), backbtn_up.height()).contains(e->pos())) {
		// Pressed backward button
		qDebug() << "Back button pressed!";
		if(m_position > 0) {
			m_position--;
		}
		repaint();
	} else if(QRect(0, height()-forwardbtn_up.height(), forwardbtn_up.width(), forwardbtn_up.height()).contains(e->pos())) {
		// Pressed forward button
		qDebug() << "Forward button pressed!";
		if(m_position < m_maximumPosition) {
			m_position++;
		}
		repaint();
	} else if(QRect(0, tmp_sliderMin+(int)(tmp_sliderStep*m_position), slider_up.width(), slider_up.height()).contains(e->pos())) {
		// Pressed slider button		
		tmp_sliderPressed = true;
		tmp_sliderPressPos = e->pos();
		tmp_sliderInitialPos = m_position;
		qDebug() << "Slider button pressed!";
	} else {
		// Pressed slider bar
	}
}

void ALyxScrollBar::mouseReleaseEvent(QMouseEvent *e) {
	if(tmp_sliderPressed) { tmp_sliderPressed = false; }
}

void ALyxScrollBar::mouseMoveEvent(QMouseEvent *e) {
	if(tmp_sliderPressed) {
			int tmp_sliderMoveSteps = (tmp_sliderPressPos.y() - e->pos().y()) / tmp_sliderStep;
			m_position = tmp_sliderInitialPos - tmp_sliderMoveSteps;
			if(m_position < 0) {
				m_position = 0;
			} else if(m_position > m_maximumPosition) {
				m_position = m_maximumPosition;
			}
			repaint();
	}
}
