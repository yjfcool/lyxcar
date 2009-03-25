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
}

ALyxDisplay::~ALyxDisplay() {
	qDebug() << "ALyxDialog destroyed";
}

void ALyxDisplay::createLayout(QString layoutName) {
	if(layoutName != "") {
		ALyxDisplayLayout layout;
		m_layouts.insert(layoutName, layout);
	} else {
		qDebug() << "Can't create layout with empty name";
	}
}

void ALyxDisplay::insertWidget(QString layoutName, QWidget *widget) {
	if(widget != NULL) {
		m_layouts[layoutName] << qobject_cast<ALyxControl *>(widget);
		widget->setParent(qobject_cast<QWidget*>(this));
	} else {
		qDebug() << "Can't insert NULL widget to display layout";
	}
}

QStringList ALyxDisplay::layouts() {

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
