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
}

void playlistmgrModuleWidget::animateReverse() {

}

playlistmgrModuleWidget::~playlistmgrModuleWidget() {
	qDebug() << "playlistmgrModuleWidget destroyed";	
}

/* SLOT
 * We use this function when we need to activate another module from current module.
 * The name of module to be activated is defined by objectName of a caller.
 * For example, if we have a button called "foo", and associated with module "bar"
 * we need to use substitution table to access "bar".
*/
void playlistmgrModuleWidget::activateModule() {
	qDebug() << "activateModule recieved objectName" << sender()->objectName();

	emit activateClicked(sender()->objectName());
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
	moduleWidget = new playlistmgrModuleWidget(parent, m_skinner);

	connect(moduleWidget, SIGNAL(activateClicked(QString)), this, SLOT(activateModuleWidget(QString)));

	return moduleWidget;
}

void playlistmgrModule::deactivate(QString deactivateFor) {
	qDebug() << "Deactivating current widget. The next module is" << deactivateFor;

	// It's needed to pass net module name to properly deactivate this and activate next module!
	nextModuleName = deactivateFor;
	connect(moduleWidget, SIGNAL(animationFinished()), this, SLOT(deactivationFinished()));
	moduleWidget->animateReverse();
}

void playlistmgrModule::deactivationFinished() {
	emit deactivated(nextModuleName);
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
