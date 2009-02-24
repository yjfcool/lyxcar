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
	
	m_position = 100;
	m_maximumPosition = 100;
	
	setAttribute(Qt::WA_NoSystemBackground, true);	
}

ALyxScrollBar::~ALyxScrollBar() {
	
}

void ALyxScrollBar::paintEvent(QPaintEvent *e) {
	QPainter p(this);
	
	p.drawPixmap(0, 0, backbtn_up);
	p.drawPixmap(0, height()-forwardbtn_up.height(), forwardbtn_up);
	
	int tmp_sliderMin = backbtn_up.height();
	int tmp_sliderLength = height()-forwardbtn_up.height()-tmp_sliderMin-backbtn_up.height();
	float tmp_sliderStep = (float)tmp_sliderLength / (float)m_maximumPosition;
//	qDebug() << "slidlength" << tmp_sliderLength << "sliderStep" << tmp_sliderStep;
	
	p.drawPixmap(0, tmp_sliderMin+(int)(tmp_sliderStep*m_position), slider_up);
	
	p.end();
}

void ALyxScrollBar::mousePressEvent(QMouseEvent *e) {

}

