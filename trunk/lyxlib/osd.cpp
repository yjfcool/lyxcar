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

#include "osd.h"

ALyxOSD::ALyxOSD(QWidget *parent) : QWidget(parent) {
    showHideTimer = new QTimer(this);
    textLabel = new QLabel(this);
    textLabel->setFont(QFont("Calibri", 26));
    textLabel->setAlignment(Qt::AlignHCenter);

    setColor(QColor("green"));

    pictureLabel = new QLabel(this);
    
    mainLayout = new QVBoxLayout(this);
    setLayout(mainLayout);
    
    mainLayout->addWidget(pictureLabel);
    mainLayout->addWidget(textLabel);

    showHideTimer->setInterval(5000);
    showHideTimer->stop();
    connect(showHideTimer, SIGNAL(timeout()), this, SLOT(hide()));

    hide();
}

ALyxOSD::~ALyxOSD() {}

void ALyxOSD::show() {
    QWidget::show();
}

void ALyxOSD::hide() {
    QWidget::hide();
    showHideTimer->stop();
}

void ALyxOSD::showOnce() {
    show();
    showHideTimer->start();
}

void ALyxOSD::inform(QString text) {
    setText(text);
    showOnce();
    raise();
}

void ALyxOSD::setShowInterval(qint8 interval) {
    showHideTimer->setInterval(interval);
}

void ALyxOSD::setColor(QColor color) {
    QPalette pal = textLabel->palette();
    pal.setColor(QPalette::WindowText, color);
    textLabel->setPalette(pal);
}

void ALyxOSD::setInfo(QPixmap image, QString text) {
    setText(text);
    setPixmap(image);
}

void ALyxOSD::setPixmap(QPixmap image) {

}

void ALyxOSD::setText(QString text) {
    textLabel->setText(text);
}
