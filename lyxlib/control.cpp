/*
 * Copyright (C) 2008-2009 Pavlov Denis
 *
 * Control prototype.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or any later version.
 *
*/

#include "control.h"

ALyxControl::ALyxControl(QWidget * parent) :
	QWidget(parent) {
	m_opacity = 1.0;
}

void ALyxControl::setFixedSize(int w, int h) {
	QWidget::setFixedSize(w, h);
	repaint();
}

void ALyxControl::setFixedSize(QSize s) {
	QWidget::setFixedSize(s);
	repaint();
}

qreal ALyxControl::opacity() const {
	return m_opacity;
}

ALyxControl::~ALyxControl() {
	qDebug() << "ALyxControl destroyed";
}
