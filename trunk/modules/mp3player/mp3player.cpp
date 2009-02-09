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

#include <QtGui>
#include <QBoxLayout>
#include <QDirModel>

#include "mp3player.h"

mp3playerWindow::mp3playerWindow(QWidget *parent) {
	setupUi(this);

	settings = new QSettings("../conf/mp3player.conf", QSettings::IniFormat, this);

	player = new MPlayerProcess(this);
	connect(player, SIGNAL(readyReadStandardOutput()), this, SLOT(playerRead()));
	connect(playBtn, SIGNAL(clicked()), this, SLOT(pauseCurrent()));

	readCurrentMedia();
	loadPlayList();

	playCurrent();
}

void mp3playerWindow::playerRead() {
	testText->append(player->readAllStandardOutput());
}

void mp3playerWindow::loadPlayList() {
	
}

void mp3playerWindow::readCurrentMedia() {
	QDirModel *model = new QDirModel;
	mediaTree->setModel(model);

	mediaTree->setRootIndex(model->index(QDir("/").absolutePath())); 
	((QHeaderView*)mediaTree->header())->hideSection(1);
	((QHeaderView*)mediaTree->header())->hideSection(2);
	((QHeaderView*)mediaTree->header())->hideSection(3);
}

void mp3playerWindow::playCurrent() {
	player->play();
}

void mp3playerWindow::stopCurrent() {
	player->write(QByteArray("stop\n"));
}

void mp3playerWindow::pauseCurrent() {
	player->write(QByteArray("pause\n"));
}

/*
 * Module activation procedure
 */
void mp3playerModule::activate(QWidget *parent) {
	moduleWindow = new mp3playerWindow();
	((QBoxLayout*)parent->layout())->insertWidget(0, moduleWindow);
}

Q_EXPORT_PLUGIN2(mp3player, mp3playerModule);
