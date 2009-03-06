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

#ifndef __JOGDIAL_H__
#define __JOGDIAL_H__

#include "control.h"
#include "skinner.h"
#include "lists.h"

class ALyxJogdial : public ALyxControl {
    Q_OBJECT
    public:
	ALyxJogdial(QWidget *parent = 0, ASkinner *s = 0);
	~ALyxJogdial();
	
	void addItem(QString text, QPixmap pixmap);
	void addItem(ALyxListWidgetItem *item);
	
	ALyxListWidgetItems items() { return m_items; }
	ALyxListWidgetItem *activeItem();
	int activeItemIndex();
	void setActiveItem(int);
	void setActiveItem(ALyxListWidgetItem *item);

    private:
	ALyxListWidgetItems m_items;
	int m_activeItemIndex;
	float m_scalePercent;
	int m_animationStep;
	
	QTimer *animationTimer;
	
	void animate();
	
	void paintEvent(QPaintEvent *e);
	void mousePressEvent(QMouseEvent *e);
	
    signals:
	void activated(ALyxListWidgetItem *);
};

#endif
