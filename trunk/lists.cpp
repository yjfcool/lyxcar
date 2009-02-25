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

#define MIN_ACCELERATION 7

#include "lists.h"
#include <QPushButton>

ALyxListWidget::ALyxListWidget(QWidget *parent, ASkinner *s) {
	l_font = QFont("Calibri", 12);
	l_paddingTop = 15;
	l_paddingLeft = 15;
	l_paddingRight = 25;
	l_paddingSelector = 5;
	l_verticalSpacing = 0;
	
	// Scrollbar paddings
	m_scrollBarPaddingTop = 15;
	m_scrollBarPaddingBottom = 15;
	m_scrollBarPaddingEdge = 15;

	m_defaultItemHeight = 65;
	m_acceleration = MIN_ACCELERATION;
	m_selectorPosition.setX(l_paddingSelector);
	m_selectorPosition.setY(0);
	m_selectedItem = 0;
	m_selectedIndex = 0;
	animationStep = 0;

	m_scrollBar = new ALyxScrollBar(this, s);
	
	setAttribute(Qt::WA_NoSystemBackground, true);

	corner_ul = QPixmap("./skins/default/list_ul.png");
	corner_bl = QPixmap("./skins/default/list_dl.png");
	corner_br = QPixmap("./skins/default/list_br.png");
	corner_ur = QPixmap("./skins/default/list_ur.png");
	top = QPixmap("./skins/default/list_u.png");
	bottom = QPixmap("./skins/default/list_b.png");
	right = QPixmap("./skins/default/list_r.png");
	left = QPixmap("./skins/default/list_l.png");
	selector = QPixmap("./skins/default/list_selector.png");
	selector_fill = QPixmap("./skins/default/list_selector_fill.png");

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
			emit selected(item);
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

	// Draw skinned frame of the listWidget
	p.drawPixmap(0, 0, corner_ul); // Upper left
	p.drawPixmap(corner_ul.width(), 0, top.scaled(width() - corner_ul.width() - corner_ur.width() - l_paddingRight, corner_ul.height())); // Top
	p.drawPixmap(0, height()-corner_bl.height(), corner_bl); // Bottom left
	p.drawPixmap(corner_bl.width(), height() - corner_bl.height(), bottom.scaled(width() - corner_bl.width() - corner_br.width()-l_paddingRight, corner_bl.height())); // Bottom
	p.drawPixmap(width()-corner_br.width()-l_paddingRight, height()-corner_br.height(), corner_br); // Bottom right
	p.drawPixmap(width()-corner_ur.width()-l_paddingRight, 0, corner_ur); // Upper right
	p.drawPixmap(width()-corner_ur.width()-l_paddingRight, corner_ur.height(), right.scaled(corner_ur.width(), height() - corner_ur.height() - corner_br.height())); // Right
	p.drawPixmap(0, corner_ul.height(), left.scaled(corner_ur.width(), height() - corner_ur.height() - corner_br.height())); // Left

	p.setBrush(QBrush(QColor("white")));
	p.setPen(QColor("white"));
	p.drawRect(corner_ul.width(),
		corner_ul.height(),
		width() - corner_ul.width() - corner_ur.width() -l_paddingRight, 
		height() - corner_ur.height() - corner_br.height());

	QImage *temporaryImage = new QImage(width(), height(), QImage::Format_ARGB32_Premultiplied);
	QPainter temporary(temporaryImage);

	// Clear transparency
	temporary.setBrush(QColor("white"));
	temporary.setCompositionMode(QPainter::CompositionMode_Clear);
	temporary.drawRect(0, 0, width(), height());
	temporary.setFont(l_font);
	temporary.setCompositionMode(QPainter::CompositionMode_SourceOver);

	// Draw selector
	if(m_selectedItem) {
		temporary.drawPixmap(m_selectorPosition, selector);
		temporary.drawTiledPixmap(m_selectorPosition.x()+selector.width(),
				  m_selectorPosition.y(),
				  width()-m_selectorPosition.x()-selector.width()-l_paddingSelector-l_paddingRight,
				  selector.height(),
				  selector_fill);
	}
	
	// Draw items
	temporary.setPen(QColor("black"));
	int cpos = l_paddingTop;
	foreach (ALyxListWidgetItem *item, items()) {
//		qDebug() << "Painted item" << item->text() << "at" << l_paddingLeft << "x" << cpos << "width" << width() << "height" << item->height();
		temporary.drawText(l_paddingLeft,
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

	temporary.setCompositionMode(QPainter::CompositionMode_DestinationIn);
	temporary.setPen(QColor(0, 255, 0, 255));
	
	// Blend bottom	
	QLinearGradient linearGrad(QPointF(0, height()-30), QPointF(0, height()-10));
	linearGrad.setColorAt(1, QColor(0, 255, 0, 0));
	linearGrad.setColorAt(0, QColor(0, 255, 0, 255));
	temporary.setBrush(QBrush(linearGrad));
	temporary.drawRect(0, height()-30, width(), height());

	// Blend top
	QLinearGradient linearGrad2(QPointF(0, 10), QPointF(0, 30));
	linearGrad2.setColorAt(0, QColor(0, 255, 0, 0));
	linearGrad2.setColorAt(1, QColor(0, 255, 0, 255));
	temporary.setBrush(QBrush(linearGrad2));
	temporary.drawRect(0, 0, width(), 30);

	// Restore composition
	temporary.setCompositionMode(QPainter::CompositionMode_SourceOver);

	temporary.end();

	p.drawImage(0, 0, *temporaryImage);
	p.end();

	m_scrollBar->setFixedSize(60, height()-m_scrollBarPaddingTop-m_scrollBarPaddingBottom);
	m_scrollBar->move(width()-m_scrollBar->width(), m_scrollBarPaddingTop);

	//m_scrollBar->repaint();
}

void ALyxListWidget::selectItem(int itemIndex) {

}

void ALyxListWidget::selectItem(ALyxListWidgetItem *item) {
	setSelectedItem(item);
}
