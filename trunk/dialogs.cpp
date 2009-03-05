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

	setOpacity(0.9);

	ALyxPushButton *btn = new ALyxPushButton(this, "OK");
	btn->setFont(QFont("Calibri", 16));
	btn->setUpPixmap(QPixmap("./skins/default/button.png"));
	btn->setDownPixmap(QPixmap("./skins/default/button_pushed.png"));

	ALyxPushButton *btn2 = new ALyxPushButton(this, tr("Cancel"));
	btn2->setFont(QFont("Calibri", 16));
	btn2->setUpPixmap(QPixmap("./skins/default/button.png"));
	btn2->setDownPixmap(QPixmap("./skins/default/button_pushed.png"));

	addButton(btn);
	addButton(btn2);

	setModal(true);

	hide();
	raise();
}

ALyxDialog::~ALyxDialog() {

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

	p.setOpacity(1);
	p.drawText(10, 20, windowTitle());

	// Draw frame
	p.setOpacity(m_opacity);
	QRect rectangle(1, 1, width()-2, height()-2);
	QPen pen(QColor("black")); pen.setWidth(2);
	p.setPen(pen);
	p.setBrush(QColor(0, 0, 0, 128));
	p.drawLine(5, 28, width()-5, 28);

#ifdef Q_OS_UNIX	p.drawRoundedRect(rectangle, 10, 10);
#endif

#ifdef Q_OS_WIN32
	p.drawRoundRect(rectangle, (int)(10.0 * ((float)height() / (float)width())), 10);
#endif

	p.end();
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
