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

#include "lists.h"

ALyxListBox::ALyxListBox(QWidget *parent, ASkinner *s) {
	l_font = QFont("Calibri", 14);
	l_paddingTop = 20;
	l_paddingLeft = 20;

	QLabel *lbl = new QLabel("<b>Hello world</b>\nHello all", this);
	lbl->setFont(l_font);
	lbl->move(l_paddingLeft, l_paddingTop);
	l_items << lbl;
}

ALyxListBox::~ALyxListBox() {}
	
void ALyxListBox::paintEvent(QPaintEvent *e) {
	QPainter p(this);
	
	p.setFont(l_font);
	
	QPixmap corner_ul("./skins/default/list_ul.png");
	QPixmap corner_bl("./skins/default/list_dl.png");
	QPixmap corner_br("./skins/default/list_br.png");
	QPixmap corner_ur("./skins/default/list_ur.png");
	QPixmap top("./skins/default/list_u.png");
	QPixmap bottom("./skins/default/list_b.png");
	QPixmap right("./skins/default/list_r.png");
	QPixmap left("./skins/default/list_l.png");
	
	p.drawPixmap(0, 0, corner_ul); // Upper left
	p.drawPixmap(corner_ul.width(), 0, top.scaled(width() - corner_ul.width() - corner_ur.width(), corner_ul.height())); // Top
	p.drawPixmap(0, height()-corner_bl.height(), corner_bl); // Bottom left
	p.drawPixmap(corner_bl.width(), height() - corner_bl.height(), bottom.scaled(width() - corner_bl.width() - corner_br.width(), corner_bl.height())); // Bottom
	p.drawPixmap(width()-corner_br.width(), height()-corner_br.height(), corner_br); // Bottom right
	p.drawPixmap(width()-corner_ur.width(), 0, corner_ur); // Upper right
	p.drawPixmap(width()-corner_ur.width(), corner_ur.height(), right.scaled(corner_ur.width(), height() - corner_ur.height() - corner_br.height())); // Right
	p.drawPixmap(0, corner_ul.height(), left.scaled(corner_ur.width(), height() - corner_ur.height() - corner_br.height())); // Left

	p.setBrush(QBrush(QColor("white")));
	p.setPen(QColor("white"));
	p.drawRect(corner_ul.width(), 
		corner_ul.height(), 
		width() - corner_ul.width() - corner_ur.width(), 
		height() - corner_ur.height() - corner_br.height());

	/*p.setPen(QColor("black"));
	p.drawText(l_paddingLeft, l_paddingTop+l_font.pointSize(), l_items[0]);*/

	// Draw skinned frame of the listbox
}
