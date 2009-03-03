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

    setOpacity(0.7);
    raise();
}

ALyxDialog::~ALyxDialog() {

}

void ALyxDialog::paintEvent(QPaintEvent *e) {
    QPainter p(this);
    p.setOpacity(m_opacity);

    p.setRenderHints(QPainter::Antialiasing);
    p.setFont(QFont("Calibri", 12));
    p.drawText(10, 20, "Dialog title");

    QRect rectangle(1, 1, width()-2, height()-2);
    QPen pen(QColor("black")); pen.setWidth(2);
    p.setPen(pen);
    p.setBrush(QColor(0, 0, 0, 128));
    p.drawLine(5, 28, width()-5, 28);
    p.drawRoundedRect(rectangle, 10, 10);

    p.end();
}
