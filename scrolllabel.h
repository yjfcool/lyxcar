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

//! \brief ALyxScrollLabel implements scrolling text.
/*!
	Scrolled text has some important parametes such as:
	<ul>
		<li>text</li>
		<li>speed</li>
		<li>step width</li>
		<li>scroll start delay</li>
		<li>edge blend size</li>
		<li>fixed width</li>
	</ul>

	The maximum <b>speed</b> of scrolling is 999 that means the delay between steps
	is 1ms. The <b>speed</b> of 0 means one step in a second.

	<b>Step</b> width is defined in pixels.

	Scroll start <b>delay</b> in <i>ms</i> means when startScroll() slot is executed the label
	does not scroll for delay time and than begins to scroll.

	<b>Edge blend size</b> is a width of edge gradients on the left and right edges
	of a label. When there is room for label text edge blends aren't displayed.

	If the fixed width is set:
        <ul>
		<li>width of a label isn't calculated to fit it's text (no autosizing)</li>
		<li>label's text is scrolling when there is no room for text in it.</li>
	</ul>
*/
class ALyxScrollLabel : public ALyxControl {
    Q_OBJECT
    public:
	//! \brief Constructs new label object with parent.
	ALyxScrollLabel(QWidget *parent = 0, QString text = "");
	~ALyxScrollLabel();

	//! \brief Set text of a label
	void setText(QString text);
	//! \brief Return text of a label
	QString text() { return m_text; }

	//! \brief Set speed of label scrolling animation
	void setSpeed(int speed) { m_speed = speed; scrollTimer->setInterval(1000-m_speed); }
	//! \brief Get speed of label scrolling animation
	int speed() { return m_speed; }

	//! \brief Set scroll step in pixels
	void setStep(int step) { m_step = step; }
	//! \brief Get scroll step in pixels
	int step() { return m_step; }

	//! \brief Set scroll delay	
	void setDelay(int delay) { m_delay = delay; delayTimer->setInterval(m_delay); }
	//! \brief Get scroll delay
	int delay() { return m_delay; }

	//! \brief Set scrollable flag
	void setScrollable(bool s) { m_scrollable = s; }
	//! \brief Get scrollable flag
	bool isScrollable() { return m_scrollable; }

	//! \brief Set label text color	
	void setTextColor(QColor color) { m_textColor = color; }
	//! \brief Set edge blend size
	void setBlendSize(int length);

	//! \brief Derived from ALyxControl	
	void setFixedWidth(int w);
	//! \brief Derived from ALyxControl
	void setFixedSize(int w, int h);
	//! \brief Derived from ALyxControl
	void setFixedSize(QSize size);

//	//! \brief Sets font of a label
//	void setFont(QFont font) { ALyxControl::setFont(font); update(); }

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

	bool isNoRoom() { return m_noRoom; }

    protected:
	void paintEvent(QPaintEvent *e);
	
    private slots:
	void scrollStep();

    public slots:
	//! \brief Starts the scroll animation loop.
	void startScroll();
	//! \brief Starts the scroll animation loop immediatly ignoring delay.
	void startScrollImmediate();
	//! \brief Stops the scroll animation loop.
	void stopScroll();

    signals:

};
#endif
