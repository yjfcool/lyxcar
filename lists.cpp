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
 
 Properties:
 
 - padding from frame to selector
 - padding from selector to item text
 
*/

#include "lists.h"

ALyxListBox::ALyxListBox(QWidget *parent, ASkinner *s) {
	l_font = QFont("Calibri", 14);
	l_paddingTop = 15;
	l_paddingLeft = 5;

	setAttribute(Qt::WA_NoSystemBackground, true);
	setFrameStyle(0);
	setWidgetResizable(true);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	l_viewport = new QWidget();
	l_viewport->setAttribute(Qt::WA_NoSystemBackground, true);
	setViewport(l_viewport);
	
	l_widget = new QWidget();
	l_widget->setAttribute(Qt::WA_NoSystemBackground, true);
	l_widget->setAttribute(Qt::WA_PaintOutsidePaintEvent, true);
	l_widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
	setWidget(l_widget);

	l_widget->setAutoFillBackground(false);
	
	QVBoxLayout *view_layout = new QVBoxLayout();
	view_layout->setContentsMargins(5, 15, 5, 15);
	view_layout->setSpacing(0);
	l_widget->setLayout(view_layout);

	QLabel *lbl = new QLabel("<b>Hello world</b><br/>Hello all");
	view_layout->addWidget(lbl);

	QBrush brush = QBrush();
	QPalette pal = palette();
	brush.setTexture(QPixmap("./skins/default/list_selector.png"));
	pal.setBrush(QPalette::Window, brush);
	lbl->setPalette(pal);
	lbl->setAutoFillBackground(true);

	lbl->setFont(l_font);
	lbl->setFixedHeight(65);
	lbl->move(l_paddingLeft, l_paddingTop);
	lbl->setContentsMargins(15, 0, 15, 0);
	l_items << lbl;
	
	for(int i = 0; i < 5; i++) {
		QLabel *lbl = new QLabel("<b>Hello world</b><br/>Hello all");
		view_layout->addWidget(lbl);
		lbl->setFont(l_font);
		lbl->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
		lbl->setFixedHeight(65);
		lbl->move(l_paddingLeft, l_paddingTop);
		lbl->setContentsMargins(15, 0, 15, 0);
		l_items << lbl;
	}
}

ALyxListBox::~ALyxListBox() {}
	
void ALyxListBox::paintEvent(QPaintEvent *e) {
	QPainter p(viewport());
	p.setFont(l_font);

	// Draw skinned frame of the listbox
	
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
	p.end();
	
	QScrollArea::paintEvent(e);

//	widget()->paintEvent(e);
	
//	foreach(QLabel *lbl, l_items) {
//		lbl->repaint();
//	}

	/*QPainter p2(widget());
	p2.setBrush(QBrush(QColor("red")));
	p2.setPen(QColor("white"));
	p2.drawRect(corner_ul.width(), 
		corner_ul.height(), 
		width() - corner_ul.width() - corner_ur.width(), 
		height() - corner_ur.height() - corner_br.height());
	p2.end();*/
}
