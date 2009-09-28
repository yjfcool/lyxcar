/*
 * Copyright (C) 2008-2009 Pavlov Denis
 *
 * Default main home module.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or any later version.
 *
*/

#include "playlistmgr.h"

/*
 * Widget class implementation
*/

playlistmgrModuleWidget::playlistmgrModuleWidget(QWidget *parent, ASkinner *s) {
	m_skinner = s;

	playList = new ALyxListWidget(this, m_skinner);
	playList->setSkin(NULL, "playlistmgr", "playlist");

	fileList = new ALyxFileListWidget(this, m_skinner);
	fileList->setSkin(NULL, "playlistmgr", "folderlist");
	
	connect(fileList, SIGNAL(fileActivated(QString)), this, SLOT(addToPlaylist(QString)));

	QStringList	mediaFilter;
	mediaFilter << "*.mp3" << "*.wma" << "*.ogg" << "*.flac" << "*.wav";
	fileList->setFilter(mediaFilter);

	addBtn = new ALyxButton(this, m_skinner);
	addBtn->setSkin(NULL, "playlistmgr", "addbutton");

	removeBtn = new ALyxButton(this, m_skinner);
	removeBtn->setSkin(NULL, "playlistmgr", "removebutton");

	loadBtn = new ALyxPushButton(this, tr("Load"));
	loadBtn->setFont(QFont("Calibri", 12));
	loadBtn->setSkin(m_skinner, "playlistmgr", "loadbutton");

	saveBtn = new ALyxPushButton(this, tr("Save"));
	saveBtn->setFont(QFont("Calibri", 12));
	saveBtn->setSkin(m_skinner, "playlistmgr", "savebutton");

	returnBtn = new ALyxPushButton(this, tr("Return"));
	returnBtn->setFont(QFont("Calibri", 12));
	returnBtn->setSkin(m_skinner, "playlistmgr", "returnbutton");

	playBtn = new ALyxPushButton(this, tr("Play/Stop"));
	playBtn->setFont(QFont("Calibri", 12));
	playBtn->setSkin(m_skinner, "playlistmgr", "playbutton");

	playListXML = new APlaylist("./test.playlist");
	playListXML->load();

	fillPlayList();
}

void playlistmgrModuleWidget::animateReverse() {
	emit animationFinished();
}

playlistmgrModuleWidget::~playlistmgrModuleWidget() {
	qDebug() << "playlistmgrModuleWidget destroyed";	
}

void playlistmgrModuleWidget::fillPlayList() {
	QDomNodeList entries = playListXML->m_xml.elementsByTagName("playlist").at(0).
		toElement().elementsByTagName("entry");
	qDebug() << playListXML->m_xml.toString();
	// Fill the playlist with album entries
	if(entries.count() > 0) for(int i = 0; i < entries.count(); i++) {
		QDomElement entry = entries.at(i).toElement();
		qDebug() << entry.attribute("fileName");
		ALyxListWidgetItem *item = new ALyxListWidgetItem(playListXML);
		QString songName;
		if(!entry.attribute("artist").isEmpty()) songName = entry.attribute("artist");
		if(entry.attribute("title").isEmpty()) {
			songName += entry.attribute("fileName");
		} else {
			songName += entry.attribute("title");
		}
		item->setText(songName);
		item->setPixmap(QPixmap("./skins/default/icons/cdplayer.png"));
		playList->addItem(item);
	} else {
		qDebug() << "Playlist is empty!";
	}
}

void playlistmgrModuleWidget::addToPlaylist(QString fileName) {
    playList->clear();

    playListXML->addEntry(fileList->dir().path(), fileName);
    playListXML->save();

    fillPlayList();
}

/*
 * Applet class implementation
*/
playlistmgrModuleApplet::playlistmgrModuleApplet(QWidget *parent, ASkinner *s) {
	m_skinner = s;
}

playlistmgrModuleApplet::~playlistmgrModuleApplet() {
	qDebug() << "playlistmgrApplet destroyed";
}

QWidget *playlistmgrModule::activate(QWidget *parent) {
	m_moduleWidget = new playlistmgrModuleWidget(parent, m_skinner);

	return m_moduleWidget;
}

void playlistmgrModule::deactivate(QString deactivateFor) {
	qDebug() << "Deactivating current widget. The next module is" << deactivateFor;

	// It's needed to pass net module name to properly deactivate this and activate next module!
	m_nextModuleName = deactivateFor;
	connect(m_moduleWidget, SIGNAL(animationFinished()), this, SLOT(deactivationFinished()));
	m_moduleWidget->animateReverse();
}

void playlistmgrModule::deactivationFinished() {
	emit deactivated(m_nextModuleName);
}

QWidget *playlistmgrModule::activateApplet(QWidget *parent) {
	// Create applet widget
//	appletWidget = new playlistmgrModuleApplet(NULL, m_skinner);
//	appletWidget->setSkinner(m_skinner);

	// When signal from applet is recieved (button clicked)
	// call activateWidget().
//	connect(appletWidget, SIGNAL(buttonClicked()), this, SLOT(activateMyself()));
	return NULL;
}


Q_EXPORT_PLUGIN2(home, playlistmgrModule);
