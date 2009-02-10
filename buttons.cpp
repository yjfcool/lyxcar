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

ALyxButton::ALyxButton(QWidget *parent) {
	currentState = false;
	if(isChecked()) { currentState = true; }
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
	repaint();
}

void ALyxButton::mouseReleaseEvent(QMouseEvent *e) {
	currentState = false;
	repaint();
}

void ALyxButton::paintEvent(QPaintEvent *e)  {
	QPainter painter(this);
	if(currentState) {
		if(!buttonUpImage.size().isNull()) {
			painter.drawPixmap(0, 0, buttonDownImage);
		}
	} else {
		if(!buttonDownImage.size().isNull()) {
			painter.drawPixmap(0, 0, buttonUpImage);
		}
	}
}
