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

#include "scrolllabel.h"

#include <QDebug>

ALyxScrollLabel::ALyxScrollLabel(QWidget *parent, QString text) : ALyxControl(parent) {
    m_speed = 0;
    m_step = 2;
    m_delay = 0;
    m_scrollPosition = 0;
    m_scrollable = false;
    m_textColor = QColor("red");
    m_blendSize = 40;

    scrollTimer = new QTimer(this);
    scrollTimer->setInterval(30);
    connect(scrollTimer, SIGNAL(timeout()), this, SLOT(scrollStep()));

    setText(text);
    setOpacity(1.0);
}

ALyxScrollLabel::~ALyxScrollLabel() {

}

void ALyxScrollLabel::setText(QString text) {
    m_text = text;

    QRect rect(0, 0, width(), height());
    rect = fontMetrics().boundingRect(rect, Qt::AlignLeft | Qt::AlignVCenter, m_text);
    if((minimumWidth() == maximumWidth()) && (maximumWidth() < rect.width())) {
	m_noRoom = true;	// There is no room for text
	setScrollable(true);	// Allow scrolling
	startScroll();
    } else {
	stopScroll();
    	m_noRoom = false;	// Widget has enough room for text
	setScrollable(false);	// Disallow scrolling
	resize(rect.width(), rect.height()+fontMetrics().lineSpacing()); // Text is fully suitable for width of a widget
    }

    repaint();
}

void ALyxScrollLabel::setFixedWidth(int w) { ALyxControl::setFixedWidth(w); setText(text()); }
void ALyxScrollLabel::setFixedSize(int w, int h) { ALyxControl::setFixedSize(w, h); setText(text()); }
void ALyxScrollLabel::setFixedSize(QSize size) { ALyxControl::setFixedSize(size); setText(text()); }

void ALyxScrollLabel::paintEvent(QPaintEvent *e) {
    QPainter p(this);

    QImage *temporaryImage = new QImage(width(), height(), QImage::Format_ARGB32_Premultiplied);
    QPainter temp(temporaryImage);
    temp.setFont(font());

    // Clear transparency
    temp.setBrush(QColor("white"));
    temp.setCompositionMode(QPainter::CompositionMode_Clear);
    temp.drawRect(0, 0, width(), height());
    temp.setCompositionMode(QPainter::CompositionMode_SourceOver);

    if(m_noRoom) {
	temp.setPen(m_textColor);
        temp.drawText(m_scrollPosition, height()-fontMetrics().lineSpacing(), m_text);
	// Add second instance of a text
	if(fontMetrics().boundingRect(0, 0, width(), height(), Qt::AlignLeft | Qt::AlignVCenter, m_text).width() + m_scrollPosition < width()) {
	    temp.drawText(fontMetrics().boundingRect(0, 0, width(), height(), Qt::AlignLeft | Qt::AlignVCenter, m_text).width() + m_scrollPosition, height()-fontMetrics().lineSpacing(), m_text);
	}

        temp.setCompositionMode(QPainter::CompositionMode_DestinationIn);
	temp.setPen(QColor(0, 255, 0, 255));

        // Blend left
	QLinearGradient linearGrad(QPointF(0, 1), QPointF(m_blendSize, 1));
        linearGrad.setColorAt(0, QColor(0, 255, 0, 0));
        linearGrad.setColorAt(1, QColor(0, 255, 0, 255));
        temp.setBrush(QBrush(linearGrad));
        temp.drawRect(0, 0, m_blendSize, height());

        // Blend right
        QLinearGradient linearGrad2(QPointF(width(), 1), QPointF(width() - m_blendSize, 1));
        linearGrad2.setColorAt(0, QColor(0, 255, 0, 0));
        linearGrad2.setColorAt(1, QColor(0, 255, 0, 255));
        temp.setBrush(QBrush(linearGrad2));
        temp.drawRect(width() - m_blendSize, 0, m_blendSize, height());
    } else {
        temp.drawText(0, height()-fontMetrics().lineSpacing(), m_text);
    }
    
    p.drawImage(0, 0, *temporaryImage, 0, 0, width(), height());

    p.end();
}

void ALyxScrollLabel::scrollStep() {
    m_scrollPosition-=m_step;
    update();
}

void ALyxScrollLabel::startScroll() {

}

void ALyxScrollLabel::startScrollImmediate() {
    if(isScrollable()) { scrollTimer->start(); }
}

void ALyxScrollLabel::stopScroll() {
    scrollTimer->stop();
}
