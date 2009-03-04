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

#include "buttons.h"

#include <QDebug>

ALyxButton::ALyxButton(QWidget *parent) : ALyxControl(parent) {
	currentState = false;
	//if(isChecked()) { currentState = true; }
	setParent(parent);
	animationTimer = new QTimer();
	animationTimer->setInterval(20);
	currentOpacity = 0;

	connect(animationTimer, SIGNAL(timeout()), this, SLOT(animate()));
}

void ALyxButton::setUpPixmap(QPixmap image) {
	buttonUpImage = image;
	setFixedSize(image.rect().size());
	repaint();
}

void ALyxButton::setDownPixmap(QPixmap image) {
	buttonDownImage = image;
	setFixedSize(image.rect().size());
	repaint();
}

void ALyxButton::setSkin(ASkinner *s, QString moduleName, QString buttonName) {
	QDomElement btnElement = s->skinModuleElementByName(moduleName, "button", buttonName);
	setUpPixmap(QPixmap(s->skinModuleImagePath(moduleName)+btnElement.attribute("released")));
	setDownPixmap(QPixmap(s->skinModuleImagePath(moduleName)+btnElement.attribute("pressed")));
	QDomElement rectElement = btnElement.firstChildElement("rect");
	if(!rectElement.isNull()) {
		move(rectElement.attribute("x").toInt(), rectElement.attribute("y").toInt());
		setFixedSize(rectElement.attribute("width").toInt(), rectElement.attribute("height").toInt());
	} else {
	 	qDebug() << "Warning: no initial rectangle for" << objectName() << "defined";
	}
}

void ALyxButton::mousePressEvent(QMouseEvent *e) {
	currentState = true;
	animationStep = 1;
	animationTimer->start();
	repaint();
	emit pressed();
}

void ALyxButton::mouseReleaseEvent(QMouseEvent *e) {
	currentState = false;
	animationStep = -1;
	animationTimer->start();
	repaint();
	emit released();
	emit clicked();
}

void ALyxButton::paintEvent(QPaintEvent *e)  {
	QPainter painter(this);
	painter.setOpacity(opacity());
	if(!buttonUpImage.isNull()) {
		if(width() != buttonUpImage.width()) {
			painter.drawPixmap(0, 0, buttonUpImage.scaled(width(), height()));
		} else {
			painter.drawPixmap(0, 0, buttonUpImage);
		}
	}
	painter.setOpacity(currentOpacity);
	if(!buttonDownImage.isNull()) {
		if(width() != buttonDownImage.width()) {
			painter.drawPixmap(0, 0, buttonDownImage.scaled(width(), height()));
		} else {
			painter.drawPixmap(0, 0, buttonDownImage);
		}
	}
	painter.setOpacity(opacity());
}

void ALyxButton::animate() {
	if(animationStep == 1) {
		currentOpacity+=0.1;
		if(currentOpacity >= m_opacity) {
			currentOpacity = m_opacity;
			animationTimer->stop();
		}
		repaint();
	} else if(animationStep == -1) {
		currentOpacity-=0.1;
		if(currentOpacity <= 0.0) {
			currentOpacity = 0.0;
			animationTimer->stop();
		}
		repaint();
	}
}

void ALyxButton::resizeEvent(QResizeEvent *e) {
	repaint();
}

ALyxPushButton::ALyxPushButton(QWidget *parent, QString text) : ALyxButton(parent) {
	m_text = text;
}

ALyxPushButton::~ALyxPushButton() {

}

void ALyxPushButton::setText(QString text) {
	m_text = text;
	repaint();
}

void ALyxPushButton::paintEvent(QPaintEvent *e) {
	ALyxButton::paintEvent(e);

	QPainter p(this);

	QRect textRect(0, 0, width(), height());
	p.drawText(textRect, Qt::AlignCenter, m_text);

	p.end();
}
