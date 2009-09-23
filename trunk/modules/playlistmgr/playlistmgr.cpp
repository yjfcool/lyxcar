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

playListMgrModuleWidget::playListMgrModuleWidget(QWidget *parent, ASkinner *s) {
	m_skinner = s;

	/*foreach (QString anim, animations.keys()) {
		animations[anim]->start();
	}*/
}

void playListMgrModuleWidget::animateReverse() {
/*	if(animations.count() > 0) {
		// If there is any animation object, connect the fin of it to animationFinished signal.
		// Only for reverse animation which means deactivation of a module widget.
		if(lastAnimation) {
			connect(lastAnimation, SIGNAL(finished()), this, SIGNAL(animationFinished()));
		}
		foreach (QString anim, animations.keys()) {
			animations[anim]->reverse();
		}
	}*/
}

playListMgrModuleWidget::~playListMgrModuleWidget() {
	qDebug() << "playListMgrModuleWidget destroyed";	
}

/* SLOT
 * We use this function when we need to activate another module from current module.
 * The name of module to be activated is defined by objectName of a caller.
 * For example, if we have a button called "foo", and associated with module "bar"
 * we need to use substitution table to access "bar".
*/
void playListMgrModuleWidget::activateModule() {
	qDebug() << "activateModule recieved objectName" << sender()->objectName();

	emit activateClicked(sender()->objectName());
}
	
/*
 * Applet class implementation
*/
playListMgrModuleApplet::playListMgrModuleApplet(QWidget *parent, ASkinner *s) {
	m_skinner = s;
}

playListMgrModuleApplet::~playListMgrModuleApplet() {
	qDebug() << "playlistMgrApplet destroyed";
}

QWidget *playListMgrModule::activate(QWidget *parent) {
	moduleWidget = new playListMgrModuleWidget(parent, m_skinner);

	connect(moduleWidget, SIGNAL(activateClicked(QString)), this, SLOT(activateModuleWidget(QString)));

	return moduleWidget;
}

void playListMgrModule::deactivate(QString deactivateFor) {
	qDebug() << "Deactivating current widget. The next module is" << deactivateFor;

	// It's needed to pass net module name to properly deactivate this and activate next module!
	nextModuleName = deactivateFor;
	connect(moduleWidget, SIGNAL(animationFinished()), this, SLOT(deactivationFinished()));
	moduleWidget->animateReverse();
}

void playListMgrModule::deactivationFinished() {
	emit deactivated(nextModuleName);
}

QWidget *playListMgrModule::activateApplet(QWidget *parent) {
	// Create applet widget
//	appletWidget = new playListMgrModuleApplet(NULL, m_skinner);
//	appletWidget->setSkinner(m_skinner);

	// When signal from applet is recieved (button clicked)
	// call activateWidget().
//	connect(appletWidget, SIGNAL(buttonClicked()), this, SLOT(activateMyself()));

	return NULL;
}


Q_EXPORT_PLUGIN2(home, playListMgrModule);
