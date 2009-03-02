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

#ifndef __SCROLLLABEL_H__
#define __SCROLLLABEL_H__

#include <QPainter>
#include <QTimer>
#include "control.h"

class ALyxScrollLabel : public ALyxControl {
    Q_OBJECT
    public:
	ALyxScrollLabel(QWidget *parent = 0, QString text = "");
	~ALyxScrollLabel();

	void setText(QString text);
	QString text() { return m_text; }

	void setSpeed(int speed) { m_speed = speed; }
	int speed() { return m_speed; }
	
	void setStep(int step) { m_step = step; }
	int step() { return m_step; }
	
	void setDelay(int delay) { m_delay = delay; }
	int delay() { return m_delay; }

	void setScrollable(bool s) { m_scrollable = s; }
	bool isScrollable() { return m_scrollable; }

	bool isNoRoom() { return m_noRoom; }
	
	void setTextColor(QColor color);
	void setBlendSize(int length);
	
	void setFixedWidth(int w);
	void setFixedSize(int w, int h);
	void setFixedSize(QSize size);

    private:
	QString m_text;
	int m_delay;
	int m_speed;
	int m_step;
	bool m_scrollable;
	bool m_noRoom;
	int m_scrollPosition;
	QColor m_textColor;
	int m_blendSize;
	
	QTimer *scrollTimer;
	QTimer *delayTimer;

    protected:
	void paintEvent(QPaintEvent *e);
	
    private slots:
	void scrollStep();

    public slots:
	void startScroll();
	void startScrollImmediate();
	void stopScroll();

    signals:

};
#endif
