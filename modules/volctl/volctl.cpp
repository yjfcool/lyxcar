/*
 * Copyright (C) 2008 Pavlov Denis
 *
 * Volume control module.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or any later version.
 *
*/

#include "volctl.h"

volCtlModuleApplet::volCtlModuleApplet(QWidget *parent, ASkinner *s) {
	setFixedWidth(220);

	QBoxLayout *layout = new QHBoxLayout();
	setLayout(layout);

	skinner = s; 

	QPalette pal = palette();
	QPixmap bgImg(skinner->skinModuleImage("volctl", "panel", "background"));
	QBrush brush = QBrush();
	brush.setTexture(bgImg);
	pal.setBrush(QPalette::Window, brush);
	setPalette(pal);
	setAutoFillBackground(true);

	vol_up_button = new ALyxButton(this);
	vol_down_button = new ALyxButton(this);
	vol_mute_button = new ALyxButton(this);

	vol_up_button->setUpPixmap(QPixmap(skinner->skinModuleImage("volctl", "volume_up_button", "released")));
	vol_down_button->setUpPixmap(QPixmap(skinner->skinModuleImage("volctl", "volume_down_button", "released")));
	vol_mute_button->setUpPixmap(QPixmap(skinner->skinModuleImage("volctl", "volume_mute_button", "released")));

	vol_up_button->setDownPixmap(QPixmap(skinner->skinModuleImage("volctl", "volume_up_button", "pressed")));
	vol_down_button->setDownPixmap(QPixmap(skinner->skinModuleImage("volctl", "volume_down_button", "pressed")));
	vol_mute_button->setDownPixmap(QPixmap(skinner->skinModuleImage("volctl", "volume_mute_button", "pressed")));

	connect(vol_up_button, SIGNAL(clicked()), this, SLOT(volume_up()));
	connect(vol_down_button, SIGNAL(clicked()), this, SLOT(volume_down()));
	connect(vol_mute_button, SIGNAL(clicked()), this, SLOT(volume_mute()));

	layout->setSpacing(0);
	layout->setContentsMargins(0, 0, 0, 0);
	layout->addStretch(1);
	layout->addWidget(vol_down_button);
	layout->addWidget(vol_up_button);
	layout->addWidget(vol_mute_button);
	layout->addStretch(1);
}

volCtlModuleApplet::~volCtlModuleApplet() {

}

/// @brief Volume control functions.
// Functions for increasing and decreasing volume level and for muting.
//
void volCtlModuleApplet::volume_up() {
	qDebug() << "Volume UP button pressed";
}

void volCtlModuleApplet::volume_mute() {
	qDebug() << "Volume MUTE button pressed";
}

void volCtlModuleApplet::volume_down() {
	qDebug() << "Volume DOWN button pressed";
}

void volCtlModule::activate(QWidget *parent) {

}

void volCtlModule::appendToPanel(APanel *panel, int position) {
	qDebug() << "Appending volCtl plugin to panel";

	// Create applet widget
	appletWidget = new volCtlModuleApplet(NULL, skinner);	
	appletWidget->setSkinner(skinner);

	// Insert it to panel
	panel->layout->insertWidget(position, appletWidget, 0);
}

Q_EXPORT_PLUGIN2(volCtl, volCtlModule);
