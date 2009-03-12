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
	m_scale = 0.7;
	m_animationStep = 0;
	m_animationPosition = 0;
	m_itemSpacing = 20;

	animationTimer = new QTimer(this);
	animationTimer->setInterval(20);
    
	connect(animationTimer, SIGNAL(timeout()), this, SLOT(animate()));
}

ALyxJogdial::~ALyxJogdial() {
	qDebug() << "ALyxJogdial destroyed";
}

void ALyxJogdial::clear() {
	m_items.clear();
	m_activeItemIndex = -1;
	repaint();
}

void ALyxJogdial::addItem(QString text, QPixmap pixmap) {
	ALyxListWidgetItem *i = new ALyxListWidgetItem(this, text, pixmap);
	addItem(i);  
}

void ALyxJogdial::addItem(ALyxListWidgetItem *item) {

	if(!item->pixmap().isNull()) {
//		qDebug() << "pixmap set";
		item->setWidth(item->pixmap().width());
		item->setHeight(item->pixmap().height()+32); // TODO: Plus text height!!!
	} else {
//		qDebug() << "pixmap isn't set";
		// TODO: Set text width and height!!!
		item->setWidth(32);
		item->setHeight(32);
	}
	
	m_items << item;
	if(m_activeItemIndex == -1) {
		m_activeItemIndex = 0;
	}
	repaint();
}

ALyxListWidgetItem *ALyxJogdial::activeItem() {
	if(m_activeItemIndex > -1) {
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
	repaint();
}

void ALyxJogdial::setActiveItem(ALyxListWidgetItem *item) {
	m_activeItemIndex = items().indexOf(item);
	repaint();
}

void ALyxJogdial::paintEvent(QPaintEvent *e) {
	QPainter p(this);

	QFont activeFont(p.font());
	activeFont.setPointSize(12);

	QFont passiveFont(p.font());
	passiveFont.setPointSize(8);

	int aw = 0, ah = 0, ax = 0, ay = 0;
	int nw = 0, nh = 0, nx = 0, ny = 0;
	int pw = 0, ph = 0, px = 0, py = 0;

	// Draw active item
//	qDebug() << "Current active item is" << m_activeItemIndex;
	if(m_activeItemIndex >= 0) {
		ALyxListWidgetItem *ai = m_items[m_activeItemIndex];
		aw = (int)((float)ai->width() * (1.0 - m_animationScale));
		ah = (int)((float)ai->height() * (1.0 - m_animationScale));
		ax = (int)((float)(width() - ai->width()) / 2) + (m_animationPosition * m_animationDirection);
		ay = (int)((float)(height() - ah) / 2);
		p.setFont(activeFont);
		p.setPen(ai->textColor());
 	   	p.drawText(ax, ay-20, ai->width(), 20, Qt::AlignCenter, ai->text());
		p.setFont(passiveFont);
		if(!ai->pixmap().isNull()) {
			p.drawPixmap(ax + (int)((ai->width() - aw) / 2), ay, ai->pixmap().scaled(QSize(aw, ah), Qt::KeepAspectRatio, Qt::SmoothTransformation));
		}
		ai->setRect(QRect(ax, ay, ai->pixmap().width(), ai->pixmap().height()));

		ALyxListWidgetItem *ni = NULL;
		ALyxListWidgetItem *pi = NULL;


	        // Draw inactive items from the left and the right
		if(m_activeItemIndex-1 >= 0) {
			pi = m_items[m_activeItemIndex-1];
			if(m_animationDirection > 0) {
				pw = (int)(pi->width() * (m_scale + m_animationScale));
				ph = (int)(pi->height() * (m_scale + m_animationScale));
			} else {
				pw = (int)(pi->width() * m_scale);
				ph = (int)(pi->height() * m_scale);
			}
			px = (int)((float)(width() - ai->width()) / 2) - ai->width() + (m_animationPosition * m_animationDirection) - m_itemSpacing;
			py = (int)((float)(height() - ph) / 2);
			p.setPen(pi->textColor());
			p.drawText(px, py-20, ai->width(), 20, Qt::AlignCenter, pi->text());
			if(!pi->pixmap().isNull()) {
				p.drawPixmap(px + (int)((pi->width() - pw) / 2), py, pi->pixmap().scaled(QSize(pw, ph), Qt::KeepAspectRatio, Qt::SmoothTransformation));
			}
			pi->setRect(QRect(px, py, pw, ph));
		}

		if(m_activeItemIndex+1 < m_items.count()) {
			ni = m_items[m_activeItemIndex+1];
			if(m_animationDirection < 0) {
				nw = (int)(ni->width() * (m_scale + m_animationScale));
				nh = (int)(ni->height() * (m_scale + m_animationScale));
			} else {
				nw = (int)(ni->width() * m_scale);
				nh = (int)(ni->height() * m_scale);
			}
			nx = (int)((float)(width() - ai->width()) / 2) + ai->width() + (m_animationPosition * m_animationDirection) + m_itemSpacing;
			ny = (int)((float)(height() - nh) / 2);
			p.setPen(ni->textColor());
			p.drawText(nx, ny-20, ai->width(), 20, Qt::AlignCenter, ni->text());
			if(!ni->pixmap().isNull()) {
				p.drawPixmap(nx + (int)((ni->width() - nw) / 2), ny, ni->pixmap().scaled(QSize(nw, nh), Qt::KeepAspectRatio, Qt::SmoothTransformation));
			}
			ni->setRect(QRect(nx, ny, nw, nh));
		}

		if(m_animationDirection < 0) {
			if(m_activeItemIndex+2 < m_items.count()) {
				ALyxListWidgetItem *nni = m_items[m_activeItemIndex+2];
				int nnx = 0, nny = 0, nnw = 0, nnh = 0;
				nnw = (int)(nni->width() * m_scale);
				nnh = (int)(nni->height() * m_scale);
				nnx = (int)((float)(width() - ai->width()) / 2) + ai->width() + ni->width() + (m_animationPosition * m_animationDirection)  + m_itemSpacing * 2;
				nny = (int)((float)(height() - nnh) / 2);
				p.setPen(nni->textColor());
				p.drawText(nnx, nny-20, ai->width(), 20, Qt::AlignCenter, nni->text());
				if(!nni->pixmap().isNull()) {
					p.drawPixmap(nnx + (int)((nni->width() - nnw) / 2), nny, nni->pixmap().scaled(QSize(nnw, nnh), Qt::KeepAspectRatio));
				}
				nni->setRect(QRect(nnx, nny, nnw, nnh));
			}
		} else {
			if(m_activeItemIndex-2 >= 0) {
				ALyxListWidgetItem *ppi = m_items[m_activeItemIndex-2];
				int ppx = 0, ppy = 0, ppw = 0, pph = 0;
				ppw = (int)(ppi->width() * m_scale);
				pph = (int)(ppi->height() * m_scale);
				ppx = (int)((float)(width() - ai->width()) / 2) - ai->width() - pi->width() + (m_animationPosition * m_animationDirection) - m_itemSpacing * 2;
				ppy = (int)((float)(height() - pph) / 2);
				p.setPen(ppi->textColor());
				p.drawText(ppx, ppy-20, ai->width(), 20, Qt::AlignCenter, ppi->text());
				if(!ppi->pixmap().isNull()) {
					p.drawPixmap(ppx + (int)((ppi->width() - ppw) / 2), ppy, ppi->pixmap().scaled(QSize(ppw, pph), Qt::KeepAspectRatio));
				}
				ppi->setRect(QRect(ppx, ppy, ppw, pph));
			}   
		}
	}

	p.end();

	ALyxControl::paintEvent(e);
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
		m_activeItemIndex = m_items.indexOf(ai);
		if(m_activeItemIndex > prev_selectedIndex) { m_animationDirection = 1; } else { m_animationDirection = -1; }
		emit activated(ai);
		m_animationStep = 0;

		m_animationPosition = m_items[prev_selectedIndex]->width() + m_itemSpacing;
		m_animationPositionChange = m_animationPosition / 10;
		m_animationScale = 0.3;
		m_animationScaleChange = 0.03;

		animationTimer->start();
	}
}

void ALyxJogdial::animate() {
    if(m_animationStep >= 10) {
        animationTimer->stop();
	m_animationPosition = 0;
	m_animationStep = 0;
	m_animationScaleChange = 0.0;
	m_animationDirection = 0;
    } else {
//	qDebug() << "Animation position is" << m_animationPosition;
	m_animationPosition-=m_animationPositionChange;
	m_animationScale-=m_animationScaleChange;
	m_animationStep++;
	
    }
    repaint();
}
