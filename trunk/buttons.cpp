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

}

void ALyxButton::setUpPixmap(QPixmap image) {
	buttonUpImage = image;
	repaint();
}

void ALyxButton::setDownPixmap(QPixmap image) {
	buttonDownImage = image;
	repaint();
}

void ALyxButton::paintEvent(QPaintEvent *e)  {
	QPainter painter(this);

	painter.drawPixmap(0, 0, buttonUpImage);
	painter.drawText(10, 10, "ttt");
}
