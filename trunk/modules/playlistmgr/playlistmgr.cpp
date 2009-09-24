/*
 * Copyright (C) 2008 Pavlov Denis
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

	folderList = new ALyxListWidget(this, m_skinner);
	folderList->setSkin(NULL, "playlistmgr", "folderlist");

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
}

void playlistmgrModuleWidget::animateReverse() {
	emit animationFinished();
}

playlistmgrModuleWidget::~playlistmgrModuleWidget() {
	qDebug() << "playlistmgrModuleWidget destroyed";	
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
