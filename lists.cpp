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

#define MIN_ACCELERATION 5

#include "lists.h"

ALyxListWidget::ALyxListWidget(QWidget *parent, ASkinner *s) {
	l_font = QFont("Calibri", 14);
	l_paddingTop = 15;
	l_paddingLeft = 15;
	l_paddingSelector = 5;
	l_verticalSpacing = 0;
	m_defaultItemHeight = 65;
	m_acceleration = MIN_ACCELERATION;
	m_selectorPosition.setX(l_paddingSelector);
	m_selectorPosition.setY(0);
	m_selectedItem = 0;
	m_selectedIndex = 0;
	animationStep = 0;

	setAttribute(Qt::WA_NoSystemBackground, true);

	animationTimer = new QTimer(this);
	animationTimer->setInterval(10);
	connect(animationTimer, SIGNAL(timeout()), this, SLOT(animateSelector()));
}

ALyxListWidget::~ALyxListWidget() {}

void ALyxListWidget::addItem(ALyxListWidgetItem *item) {
	item->setHeight(m_defaultItemHeight);
	l_items << item; 
	repaint();
}

void ALyxListWidget::setSelectedItem(ALyxListWidgetItem *item) {
	m_selectedItem = item;
	m_selectedIndex = l_items.indexOf(item);
	repaint();
}

void ALyxListWidget::mousePressEvent(QMouseEvent *e) {
	foreach (ALyxListWidgetItem *item, items()) {
		if(item->rect.contains(e->pos())) {
			int prev_selectedIndex = m_selectedIndex;
			setSelectedItem(item);
			if(prev_selectedIndex < m_selectedIndex) {
				animationStep = 1;
			} else if(prev_selectedIndex > m_selectedIndex) {
				animationStep = -1;
			}
			animationTimer->start();
		}
	}	
}

void ALyxListWidget::animateSelector() {
	if(animationStep != 0) {
		m_selectorPosition.setY(m_selectorPosition.y()+(m_acceleration*animationStep));
		m_acceleration++;
		if(((m_selectorPosition.y() <= m_selectedItem->rect.y() && animationStep < 0)) || 
		   ((m_selectorPosition.y() >= m_selectedItem->rect.y() && animationStep > 0))) {
			animationTimer->stop();
			m_acceleration = MIN_ACCELERATION;
			m_selectorPosition.setY(m_selectedItem->rect.y());
		}
		repaint();
	}
}

void ALyxListWidget::paintEvent(QPaintEvent *e) {
	QPainter p(this);
	p.setFont(l_font);

	// Draw skinned frame of the listWidget
	QPixmap corner_ul("./skins/default/list_ul.png");
	QPixmap corner_bl("./skins/default/list_dl.png");
	QPixmap corner_br("./skins/default/list_br.png");
	QPixmap corner_ur("./skins/default/list_ur.png");
	QPixmap top("./skins/default/list_u.png");
	QPixmap bottom("./skins/default/list_b.png");
	QPixmap right("./skins/default/list_r.png");
	QPixmap left("./skins/default/list_l.png");
	QPixmap selector("./skins/default/list_selector.png");
	QPixmap selector_fill("./skins/default/list_selector_fill.png");
	
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

	// Draw selector
	if(m_selectedItem) {
		p.drawPixmap(m_selectorPosition, selector);
		p.drawTiledPixmap(m_selectorPosition.x()+selector.width(),
				  m_selectorPosition.y(),
				  width()-m_selectorPosition.x()-selector.width()-l_paddingSelector,
				  selector.height(),
				  selector_fill);
	}
	
	// Draw items
	p.setPen(QColor("black"));
	int cpos = l_paddingTop;
	foreach (ALyxListWidgetItem *item, items()) {
//		qDebug() << "Painted item" << item->text() << "at" << l_paddingLeft << "x" << cpos << "width" << width() << "height" << item->height();
		p.drawText(l_paddingLeft,
			   cpos, 
			   width(),
			   item->height(),
			   Qt::AlignVCenter,
			   item->text()
		);
		item->rect.setX(l_paddingLeft);
		item->rect.setY(cpos);
		item->rect.setWidth(width());
		item->rect.setHeight(item->height());
		cpos+=l_verticalSpacing+item->height();
	}

	p.end();
}
