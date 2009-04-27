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

#include "playerdisplay.h"

AMp3PlayerDisplay::AMp3PlayerDisplay(QWidget *parent, ASkinner *skinner) :
		QWidget(parent)
{
	ALyxDisplay *d = new ALyxDisplay(this, skinner);

	QDomElement displayElement = skinner->skinModuleElement("mp3player", "display");
	QString background = displayElement.attribute("background");
	QString fontfamily = displayElement.attribute("font-family");
	QString fontsize = displayElement.attribute("font-size");
	qDebug() << "mp3player display background" << background << "font-family" << fontfamily << "font-size" << fontsize;

	setObjectName("mp3playerdisplay");
	d->setBackgroundPixmap(QPixmap(skinner->skinModuleImagePath("mp3player")+background));
	d->createLayout("mainLayout");

	QDomElement rectElement = displayElement.firstChildElement("rect");
	if(!rectElement.isNull()) {
		d->move(0, 0);
		d->setFixedSize(rectElement.attribute("width").toInt(), rectElement.attribute("height").toInt());
		move(rectElement.attribute("x").toInt(), rectElement.attribute("y").toInt());
		setFixedSize(rectElement.attribute("width").toInt(), rectElement.attribute("height").toInt());
	} else {
		qDebug() << "Warning: no initial rectangle for" << objectName() << "defined";
	}

	songTitleLbl = new ALyxScrollLabel(d);
	songTitleLbl->setSpeed(980);
	songTitleLbl->setStep(1);
	songTitleLbl->setDelay(1000);
	songTitleLbl->setTextColor(QColor("black"));
	songTitleLbl->setFont(QFont("Calibri", 20));
	songTitleLbl->setText(tr("- NO TITLE -"));
	songTitleLbl->move(20, 10);
	songTitleLbl->setFixedWidth(250);

	songDurationLbl = new QLabel(d);
	songDurationLbl->setFont(QFont("Calibri", 24));
	songDurationLbl->setText("--:--");
	songDurationLbl->move(290, 20);
	songDurationLbl->setFixedWidth(100);

	playIcon = new QLabel(d);
	playIcon->setPixmap(QPixmap());
	playIcon->move(400, 10);
	playIcon->setFixedSize(24, 24);

	pausedIcon = new QLabel(d);
	pausedIcon->setPixmap(QPixmap());
	pausedIcon->move(400, 40);
	pausedIcon->setFixedSize(24, 24);

	repeatIcon = new QLabel(d);
	repeatIcon->setPixmap(QPixmap("./skins/default/mp3player/icons/playforward.png"));
	repeatIcon->move(400, 70);
	repeatIcon->setFixedSize(24, 24);

	d->insertWidget("mainLayout", songTitleLbl);
	d->insertWidget("mainLayout", songDurationLbl);
}

AMp3PlayerDisplay::~AMp3PlayerDisplay() {
	qDebug() << "AMp3PlayerDisplay destroyed";
}

void AMp3PlayerDisplay::setSongDuration(QString duration) {
	songDurationLbl->setText(duration);
}

void AMp3PlayerDisplay::setSongTitle(QString title) {
	songTitleLbl->stopScroll();
	songTitleLbl->setText(title);
	songTitleLbl->startScroll();
}

void AMp3PlayerDisplay::setPlaying(bool isPlaying) {
	if(isPlaying) {
		playIcon->setPixmap(QPixmap("./skins/default/mp3player/icons/playing.png"));
	} else {
		playIcon->setPixmap(QPixmap());
	}
}

void AMp3PlayerDisplay::setPaused(bool isPaused) {
	if(isPaused) {
		pausedIcon->setPixmap(QPixmap("./skins/default/mp3player/icons/paused.png"));
	} else {
		pausedIcon->setPixmap(QPixmap());
	}
}

void AMp3PlayerDisplay::setRepeat(bool repeat) {
	if(repeat) {
		repeatIcon->setPixmap(QPixmap("./skins/default/mp3player/icons/playrepeat.png"));
	} else {
		repeatIcon->setPixmap(QPixmap("./skins/default/mp3player/icons/playforward.png"));
	}
}
