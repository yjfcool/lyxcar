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

#include "jogdial.h"

ALyxJogdial::ALyxJogdial(QWidget *parent, ASkinner *s) : 
    ALyxControl(parent) {
    m_activeItemIndex = -1;
    m_scalePercent = 0.8;
    m_animationStep = 0;
    
    animationTimer = new QTimer(this);
    animationTimer->setInterval(10);
    
    connect(animationTimer, SIGNAL(timeout()), this, SLOT(animate()));
}

ALyxJogdial::~ALyxJogdial() {
    qDebug() << "ALyxJogdial destroyed";
}

void ALyxJogdial::addItem(QString text, QPixmap pixmap) {
    ALyxListWidgetItem *i = new ALyxListWidgetItem(this);
    i->setText(text);
    i->setPixmap(pixmap);
    if(!pixmap.isNull()) {
	qDebug() << "pixmap set";
	i->setWidth(pixmap.width());
	i->setHeight(pixmap.height()+32); // TODO: Plus text height!!!
    } else {
	qDebug() << "pixmap isn't set";
	// TODO: Set text width and height!!!
	i->setWidth(32);
	i->setHeight(32);
    }
    m_items << i;
    if(m_activeItemIndex == -1) {
	m_activeItemIndex = 0;
    }
    
    repaint();
}

void ALyxJogdial::addItem(ALyxListWidgetItem *item) {
    m_items << item;
}

ALyxListWidgetItem *ALyxJogdial::activeItem() {
    if(m_activeItemIndex > 0) {
        return m_items[m_activeItemIndex];
    } else {
	return NULL;
    }
}

int ALyxJogdial::activeItemIndex() {
    return m_activeItemIndex;
}

void ALyxJogdial::setActiveItem(int index) {
    m_activeItemIndex = index;
}

void ALyxJogdial::setActiveItem(ALyxListWidgetItem *item) {
    m_activeItemIndex = items().indexOf(item);
    repaint();
}

void ALyxJogdial::paintEvent(QPaintEvent *e) {
    QPainter p(this);

    // Draw active item
    qDebug() << "Current active item is" << m_activeItemIndex;
    if(m_activeItemIndex >= 0) {
	ALyxListWidgetItem *ai = m_items[m_activeItemIndex];
	int ax = (int)((float)width() / 2 - (float)ai->width() / 2);
	int ay = (int)((float)height() / 2 - (float)ai->height() / 2);
    	p.drawText(ax, ay-10, ai->text());
    	p.drawPixmap(ax, ay, ai->pixmap());
	ai->setRect(QRect(ax, ay, ai->pixmap().width(), ai->pixmap().height()));
    }
    
    // Draw inactive items from the left and the right
    if(m_activeItemIndex-1 >= 0) {
	ALyxListWidgetItem *ai = m_items[m_activeItemIndex-1];
	int ax = (int)((float)width() / 2 - (float)ai->width() / 2) - ai->width() - 20;
	int ay = (int)((float)height() / 2 - (float)ai->height() / 2);
	int aw = (int)(ai->width() * m_scalePercent);
	int ah = (int)(ai->height() * m_scalePercent);
    	p.drawText(ax, ay-10, ai->text());
    	p.drawPixmap(ax, ay, ai->pixmap().scaled(QSize(aw, ah), Qt::KeepAspectRatio));
	ai->setRect(QRect(ax, ay, aw, ah));
    }

    if(m_activeItemIndex+1 < m_items.count()) {
	ALyxListWidgetItem *ai = m_items[m_activeItemIndex+1];
	int ax = (int)((float)width() / 2 - (float)ai->width() / 2) + ai->width() + 20;
	int ay = (int)((float)height() / 2 - (float)ai->height() / 2);
	int aw = (int)(ai->width() * m_scalePercent);
	int ah = (int)(ai->height() * m_scalePercent);
    	p.drawText(ax, ay-10, ai->text());
    	p.drawPixmap(ax, ay, ai->pixmap().scaled(QSize(aw, ah), Qt::KeepAspectRatio));
	ai->setRect(QRect(ax, ay, aw, ah));
    }
    
    p.end();
}

void ALyxJogdial::mousePressEvent(QMouseEvent *e) {
	ALyxListWidgetItem *ai = NULL;
	foreach (ALyxListWidgetItem *item, items()) {
		if((item->rect().contains(e->pos())) &&
	    	    ((items().indexOf(item) == m_activeItemIndex-1) || 
		    (items().indexOf(item) == m_activeItemIndex+1))) {
			ai = item;
    		}

	}
	if(ai != NULL) {
		int prev_selectedIndex = m_activeItemIndex;
		setActiveItem(ai);
		emit activated(ai);
		if(prev_selectedIndex < m_activeItemIndex) {
			m_animationStep = 1;
		} else if(prev_selectedIndex > m_activeItemIndex) {
			m_animationStep = -1;
		}
		animationTimer->start();
	}
}

void ALyxJogdial::animate() {
    animationTimer->stop();
}
