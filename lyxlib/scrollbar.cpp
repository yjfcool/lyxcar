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

#define FAST_INTERVAL 10
#define SLOW_INTERVAL 150

ALyxScrollBar::ALyxScrollBar(QWidget *parent, ASkinner *s) : QWidget(parent) {
	m_skinner = s;
	
	backbtn_up = QPixmap("./skins/default/list_up_btn.png");
	backbtn_down = QPixmap("./skins/default/list_up_btn.png");
	forwardbtn_up = QPixmap("./skins/default/list_dn_btn.png");
	forwardbtn_down = QPixmap("./skins/default/list_dn_btn.png");
	slider_up = QPixmap("./skins/default/scroller.png");
	slider_down = QPixmap("./skins/default/scroller.png");

	tmp_sliderPressed = false;
	
	m_position = 0;
	m_minimumPosition = 0;
	m_maximumPosition = 1;
	m_singleStep = 1;

	scrollRepeatTimer = new QTimer(this);
	scrollRepeatTimer->setInterval(SLOW_INTERVAL);
	connect(scrollRepeatTimer, SIGNAL(timeout()), this, SLOT(scrollRepeat()));
	
	setAttribute(Qt::WA_NoSystemBackground, true);	
}

ALyxScrollBar::~ALyxScrollBar() {
	
}

void ALyxScrollBar::resizeEvent(QResizeEvent *e) {
	calculateSliderButton();
}

void ALyxScrollBar::calculateSliderButton() {
	// Calculate slider button position
	tmp_sliderMin = backbtn_up.height();
	tmp_sliderLength = height()-forwardbtn_up.height()-tmp_sliderMin-backbtn_up.height();
	tmp_sliderStep = (float)tmp_sliderLength / (float)(m_maximumPosition-m_minimumPosition);
}

void ALyxScrollBar::paintEvent(QPaintEvent *e) {
	QPainter p(this);
	
	p.drawPixmap(0, 0, backbtn_up);
	p.drawPixmap(0, height()-forwardbtn_up.height(), forwardbtn_up);
	p.drawPixmap(0, tmp_sliderMin+(int)(tmp_sliderStep*(m_position-m_minimumPosition)), slider_up);

	qDebug() << "Drawing slider at" << (m_position-m_minimumPosition);
	
	p.end();
}

void ALyxScrollBar::mousePressEvent(QMouseEvent *e) {
	if(QRect(0, 0, backbtn_up.width(), backbtn_up.height()).contains(e->pos())) {
		// Pressed backward button
		qDebug() << "Back button pressed!";
		if(m_position > m_minimumPosition) {
			m_position-=m_singleStep;
			if(m_position < m_minimumPosition) { m_position = m_minimumPosition; }
			emit changed(m_position, -1);

			// Run scroll timer
			scrollRepeatDirection = -1;
			scrollRepeatTimer->start();
		}
		repaint();
	} else if(QRect(0, height()-forwardbtn_up.height(), forwardbtn_up.width(), forwardbtn_up.height()).contains(e->pos())) {
		// Pressed forward button
		qDebug() << "Forward button pressed!";
		if(m_position < m_maximumPosition) {
			m_position+=m_singleStep;
			if(m_position > m_maximumPosition) { m_position = m_maximumPosition; }
			emit changed(m_position, 1);

			// Run scroll timer
			scrollRepeatDirection = 1;
			scrollRepeatTimer->start();
		}
		repaint();
	} else if(QRect(0, tmp_sliderMin+(int)(tmp_sliderStep*(m_position-m_minimumPosition)), slider_up.width(), slider_up.height()).contains(e->pos())) {
		// Pressed slider button		
		tmp_sliderPressed = true;
		tmp_sliderPressPos = e->pos();
		tmp_sliderInitialPos = m_position;
		emit changed(m_position, 0);
		qDebug() << "Slider button pressed!";
	} else {
		// Pressed slider bar
	}
}

void ALyxScrollBar::mouseReleaseEvent(QMouseEvent *e) {
	// Initial state of scroll timer
	scrollRepeatTimer->setInterval(SLOW_INTERVAL);
	scrollRepeatTimer->stop();

	if(tmp_sliderPressed) { tmp_sliderPressed = false; }
}

void ALyxScrollBar::mouseMoveEvent(QMouseEvent *e) {
	if(tmp_sliderPressed) {
			int tmp_sliderMoveSteps = (tmp_sliderPressPos.y() - e->pos().y()) / tmp_sliderStep;
			m_position = tmp_sliderInitialPos - tmp_sliderMoveSteps;
			if(m_position < m_minimumPosition) {
				m_position = m_minimumPosition;
			} else if(m_position > m_maximumPosition) {
				m_position = m_maximumPosition;
			}
			repaint();
	}
}

void ALyxScrollBar::scrollRepeat() {
	if((m_position > m_minimumPosition) && (m_position < m_maximumPosition)) {
		if(scrollRepeatTimer->interval() == SLOW_INTERVAL) {
			scrollRepeatTimer->setInterval(FAST_INTERVAL);
		}
		m_position+=scrollRepeatDirection*m_singleStep;
		if(m_position < m_minimumPosition) { m_position = m_minimumPosition; }
		else if(m_position > m_maximumPosition) { m_position = m_maximumPosition; }
		emit changed(m_position, scrollRepeatDirection);
		repaint();
	}
}
