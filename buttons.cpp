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

#include "buttons.h"

#include <QDebug>

ALyxButton::ALyxButton(QWidget *parent) : ALyxControl(parent) {
	currentState = false;
	//if(isChecked()) { currentState = true; }
	setParent(parent);
	animationTimer = new QTimer();
	animationTimer->setInterval(20);
	currentOpacity = 0;

	connect(animationTimer, SIGNAL(timeout()), this, SLOT(animate()));
}

void ALyxButton::setUpPixmap(QPixmap image) {
	buttonUpImage = image;
	setFixedSize(image.rect().size());
	repaint();
}

void ALyxButton::setDownPixmap(QPixmap image) {
	buttonDownImage = image;
	setFixedSize(image.rect().size());
	repaint();
}

void ALyxButton::mousePressEvent(QMouseEvent *e) {
	currentState = true;
	animationStep = 1;
	animationTimer->start();
	repaint();
	emit pressed();
}

void ALyxButton::mouseReleaseEvent(QMouseEvent *e) {
	currentState = false;
	animationStep = -1;
	animationTimer->start();
	repaint();
	emit released();
	emit clicked();
}

void ALyxButton::paintEvent(QPaintEvent *e)  {
	QPainter painter(this);
	painter.setOpacity(opacity());
	if(width() != buttonUpImage.width()) {
	    painter.drawPixmap(0, 0, buttonUpImage.scaled(width(), height()));
	} else {
	    painter.drawPixmap(0, 0, buttonUpImage);
	}
	painter.setOpacity(currentOpacity);
	if(width() != buttonDownImage.width()) {
	    painter.drawPixmap(0, 0, buttonDownImage.scaled(width(), height()));
	} else {
	    painter.drawPixmap(0, 0, buttonDownImage);
	}
	painter.setOpacity(opacity());
}

void ALyxButton::animate() {
	if(animationStep == 1) {
		currentOpacity+=0.1;
		if(currentOpacity >= m_opacity) {
			currentOpacity = m_opacity;
			animationTimer->stop();
		}
		repaint();
	} else if(animationStep == -1) {
		currentOpacity-=0.1;
		if(currentOpacity <= 0.0) {
			currentOpacity = 0.0;
			animationTimer->stop();
		}
		repaint();
	}
}

void ALyxButton::resizeEvent(QResizeEvent *e) {
	repaint();
}
