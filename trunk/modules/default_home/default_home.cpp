/*
 * Copyright (C) 2008 Pavlov Denis
 *
 * Main home module.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or any later version.
 *
*/

#include "default_home.h"

/*
 * Widget class implementation
*/

homeModuleWidget::homeModuleWidget(QWidget *parent, ASkinner *s) {
    m_skinner = s;
}

homeModuleWidget::~homeModuleWidget() {

}

/*
 * Applet class implementation
*/

homeModuleApplet::homeModuleApplet(QWidget *parent, ASkinner *s) {
    m_skinner = s;
}

homeModuleApplet::~homeModuleApplet() {

}

QWidget *homeModule::activate(QWidget *parent) {

}

QWidget *homeModule::activateApplet(QWidget *parent) {
	qDebug() << "Appending default_home plugin to panel";

	// Create applet widget
	appletWidget = new homeModuleApplet(NULL, skinner);
	appletWidget->setSkinner(skinner);

	return appletWidget;
}
