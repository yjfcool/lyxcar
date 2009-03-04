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

ALyxDialog::ALyxDialog(QWidget *parent) : ALyxControl(parent) {

	setOpacity(0.9);

	ALyxPushButton *btn = new ALyxPushButton(this, "OK");
	btn->move(100, 240);
	btn->setFont(QFont("Calibri", 16));
	btn->setUpPixmap(QPixmap("./skins/default/button.png"));
	btn->setDownPixmap(QPixmap("./skins/default/button_pushed.png"));
	btn->setFixedSize(140, 48);

	ALyxPushButton *btn2 = new ALyxPushButton(this, tr("Cancel"));
	btn2->move(250, 240);
	btn2->setFont(QFont("Calibri", 16));
	btn2->setUpPixmap(QPixmap("./skins/default/button.png"));
	btn2->setDownPixmap(QPixmap("./skins/default/button_pushed.png"));
	btn2->setFixedSize(140, 48);

	raise();
}

ALyxDialog::~ALyxDialog() {

}

void ALyxDialog::paintEvent(QPaintEvent *e) {
	QPainter p(this);

	// Draw header
	p.setRenderHints(QPainter::Antialiasing);
	p.setFont(QFont("Calibri", 12));
	p.setPen(QColor("white"));
	p.setBrush(QColor("white"));

	p.setOpacity(1);
	p.drawText(10, 20, "Dialog title");

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
