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

mp3playerWindow::mp3playerWindow(QWidget *parent, ASkinner *s) {
	m_skinner = s;

	qDebug() << "mp3player is reading player settings";
	settings = new QSettings("../conf/mp3player.conf", QSettings::IniFormat, this);

	qDebug() << "mp3player creates it's window";
	createWindow();
	
	ALyxDialog *dialog = new ALyxDialog(this);
	dialog->setWindowTitle(tr("Common dialog"));
	dialog->move(100, 100);
	dialog->setFixedSize(500, 300);
	dialog->raise();

//	player = new MPlayerProcess(this);
//	connect(player, SIGNAL(readyReadStandardOutput()), this, SLOT(playerRead()));
//	connect(playBtn, SIGNAL(clicked()), this, SLOT(pauseCurrent()));

//	readCurrentMedia();
//	loadPlayList();

//	playCurrent();
}

void mp3playerWindow::createWindow() {
	ALyxDisplay *display = new ALyxDisplay(this);

	playBtn = new ALyxButton(this);
	firstBtn = new ALyxButton(this);
	backBtn = new ALyxButton(this);
	nextBtn = new ALyxButton(this);
	lastBtn = new ALyxButton(this);
	
	ALyxListWidget *playList= new ALyxListWidget(this, m_skinner);
	playList->move(450, 10);
	playList->setFixedSize(330, 390);

	QDomElement displayElement = m_skinner->skinModuleElement("mp3player", "display");
	QString background = displayElement.attribute("background");
	QString fontfamily = displayElement.attribute("font-family");
	QString fontsize = displayElement.attribute("font-size");
	qDebug() << "mp3player display background" << background << "font-family" << fontfamily << "font-size" << fontsize;

	display->setObjectName("display");
	display->setBackgroundPixmap(QPixmap(m_skinner->skinModuleImagePath("mp3player")+background));

	QDomElement rectElement = displayElement.firstChildElement("rect");
	if(!rectElement.isNull()) {
		display->move(rectElement.attribute("x").toInt(), rectElement.attribute("y").toInt());
		display->setFixedSize(rectElement.attribute("width").toInt(), rectElement.attribute("height").toInt());
	} else {
	 	qDebug() << "Warning: no initial rectangle for" << display->objectName() << "defined";
	}

	playBtn->setSkin(m_skinner, "mp3player", "play");
	firstBtn->setSkin(m_skinner, "mp3player", "first");
	backBtn->setSkin(m_skinner, "mp3player", "back");
	lastBtn->setSkin(m_skinner, "mp3player", "last");
	nextBtn->setSkin(m_skinner, "mp3player", "next");
}

void mp3playerWindow::playerRead() {
	//testText->append(player->readAllStandardOutput());
}

void mp3playerWindow::loadPlayList() {
	
}

void mp3playerWindow::readCurrentMedia() {
	/*QDirModel *model = new QDirModel;
	mediaTree->setModel(model);

	mediaTree->setRootIndex(model->index(QDir("/").absolutePath())); 
	((QHeaderView*)mediaTree->header())->hideSection(1);
	((QHeaderView*)mediaTree->header())->hideSection(2);
	((QHeaderView*)mediaTree->header())->hideSection(3);*/
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
QWidget * mp3playerModule::activate(QWidget *parent) {
	moduleWindow = new mp3playerWindow(parent, m_skinner);

	return moduleWindow;
}
void mp3playerModule::deactivate(QString deactivateFor) {
    emit deactivated(deactivateFor);
}

QWidget * mp3playerModule::activateApplet(QWidget *parent) {
	return 0;
}

Q_EXPORT_PLUGIN2(mp3player, mp3playerModule);
