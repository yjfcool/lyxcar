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

#include "dialogs.h"

ALyxDialog::ALyxDialog(QWidget *parent, ASkinner *s) : ALyxControl(parent) {
	setModal(true);

	raise();
//	hide();
}

ALyxDialog::~ALyxDialog() {
	// Restore accessibility before deletion
//	setModal(false);

	qDebug() << "ALyxDialog desroyed";
}

void ALyxDialog::center() {
	int x = (qobject_cast<QWidget*>(parent())->width() - width()) / 2;
	int y = (qobject_cast<QWidget*>(parent())->height() - height()) / 2;

	move(x, y);
}

void ALyxDialog::setModal(bool modality) {
	QObjectList ch = parent()->children();
	for(int i = 0; i < ch.count(); i++) {
		if((ch[i]->isWidgetType()) && ch[i] != this) {
			qobject_cast<QWidget *>(ch[i])->setEnabled(!modality);
		}
	}
}

void ALyxDialog::paintEvent(QPaintEvent *e) {
	QPainter p(this);

	// Draw header
	p.setRenderHints(QPainter::Antialiasing);
	p.setFont(QFont("Calibri", 12));
	p.setPen(QColor("white"));
	p.setBrush(QColor("white"));


	p.setPen(QColor("white"));
	p.drawText(10, 20, windowTitle());

	// Draw frame
	QRect rectangle(1, 1, width()-2, height()-2);
	QPen pen(QColor("black")); pen.setWidth(2);
	p.setPen(pen);
	p.setBrush(QColor(0, 0, 0, 128));
	p.drawLine(5, 28, width()-5, 28);

#ifdef Q_OS_UNIX
	p.drawRoundedRect(rectangle, 10, 10);
#endif

#ifdef Q_OS_WIN32
	p.drawRoundRect(rectangle, (int)(10.0 * ((float)height() / (float)width())), 10);
#endif

	p.end();

	ALyxControl::paintEvent(e);
}

void ALyxDialog::resizeEvent(QResizeEvent *e) {
	int index = 0;
	foreach(ALyxButton *btn, m_buttons) {
		m_buttons[index]->move(
			index * (m_buttons[index]->width() + 10) + 10, 
			height() - m_buttons[index]->height() - 10
		);
		index++;
	}
}

void ALyxDialog::buttonReaction() {
	QString name = sender()->objectName();
 	emit buttonClicked(name);
}
