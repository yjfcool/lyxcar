/*
 * Copyright (C) 2008-2009 Pavlov Denis
 *
 * Comments unavailable.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or any later version.
 *
*/

#include "display.h"

ALyxDisplay::ALyxDisplay(QWidget *parent) : ALyxControl(parent) {
	ALyxScrollLabel *lbl = new ALyxScrollLabel(this);
	lbl->setSpeed(980);
	lbl->setStep(1);
	lbl->setDelay(1000);
	lbl->setTextColor(QColor("black"));
	lbl->setFont(QFont("Calibri", 20));
	lbl->setText("My favorite song - Song number one *** ");
	lbl->move(20, 10);
	lbl->setFixedWidth(250);
	lbl->startScroll();

	ALyxScrollLabel *timeLbl = new ALyxScrollLabel(this);
	timeLbl->setSpeed(980);
	timeLbl->setStep(1);
	timeLbl->setDelay(1000);
	timeLbl->setTextColor(QColor("black"));
	timeLbl->setFont(QFont("Calibri", 37));
	timeLbl->setText("32:21");
	timeLbl->move(290, 0);
	timeLbl->setFixedWidth(130);
	timeLbl->startScroll();

	ALyxDisplayLayout layout1;
	layout1 << lbl;
	layout1 << timeLbl;
	m_layouts.insert("layout1", layout1);

	activateLayout("layout1");
}

ALyxDisplay::~ALyxDisplay() {
	qDebug() << "ALyxDialog destroyed";
}

void ALyxDisplay::activateLayout(QString layoutName) {
	
}

void ALyxDisplay::paintEvent(QPaintEvent *e) {
	QPainter p(this);
	if(!m_background.isNull()) {
		p.drawPixmap(0, 0, m_background, 0, 0, width(), height());
	}
	p.end();
}
