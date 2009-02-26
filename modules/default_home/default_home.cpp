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

	ALyxButton *button1 = new ALyxButton(this);
	button1->setUpPixmap(QPixmap("skins/default/default_home/mp3_btn_up.png"));
	button1->setDownPixmap(QPixmap("skins/default/default_home/mp3_btn_down.png"));

	ALyxAnimation *anim1 = new ALyxAnimation(this, button1);
	anim1->setAnimationTime(20);
	anim1->stops << ALyxAnimationStop(0, -276, 20, 276, 94);
	anim1->stops << ALyxAnimationStop(15, 10, 20, 276, 94);
	anim1->stops << ALyxAnimationStop(20, 20, 20, 276, 94);

	ALyxButton *button2 = new ALyxButton(this);
	button2->setUpPixmap(QPixmap("skins/default/default_home/video_btn_up.png"));
	button2->setDownPixmap(QPixmap("skins/default/default_home/video_btn_down.png"));

	ALyxAnimation *anim2 = new ALyxAnimation(this, button2);
	anim2->setAnimationTime(30);
	anim2->stops << ALyxAnimationStop(0, -276, 140, 276, 94);
	anim2->stops << ALyxAnimationStop(10, -276, 140, 276, 94);
	anim2->stops << ALyxAnimationStop(25, 10, 140, 276, 94);
	anim2->stops << ALyxAnimationStop(30, 20, 140, 276, 94);

	ALyxButton *button3 = new ALyxButton(this);
	button3->setUpPixmap(QPixmap("skins/default/default_home/gps_btn_up.png"));
	button3->setDownPixmap(QPixmap("skins/default/default_home/gps_btn_down.png"));

	ALyxAnimation *anim3 = new ALyxAnimation(this, button3);
	anim3->setAnimationTime(40);
	anim3->stops << ALyxAnimationStop(0, -276, 260, 276, 94);
	anim3->stops << ALyxAnimationStop(20, -276, 260, 276, 94);
	anim3->stops << ALyxAnimationStop(30, -276, 260, 276, 94);
	anim3->stops << ALyxAnimationStop(35, 10, 260, 276, 94);
	anim3->stops << ALyxAnimationStop(40, 20, 260, 276, 94);

	anim1->start();
	anim2->start();
	anim3->start();

}

homeModuleWidget::~homeModuleWidget() {

}

/*
 * Applet class implementation
*/

homeModuleApplet::homeModuleApplet(QWidget *parent, ASkinner *s) {
	m_skinner = s;

	ALyxButton *button = new ALyxButton(this);

	button->setUpPixmap(QPixmap(m_skinner->skinModuleImage("default_home", "button", "released")));
	button->setDownPixmap(QPixmap(m_skinner->skinModuleImage("default_home", "button", "pressed")));

	// When the button is clicked emit signal from an applet
	connect(button, SIGNAL(clicked()), this, SIGNAL(buttonClicked()));

	setFixedWidth(button->width());
}

homeModuleApplet::~homeModuleApplet() {

}

QWidget *homeModule::activate(QWidget *parent) {
	moduleWidget = new homeModuleWidget(parent, skinner);

	return moduleWidget;
}

QWidget *homeModule::activateApplet(QWidget *parent) {
	qDebug() << "Appending default_home plugin to panel";

	// Create applet widget
	appletWidget = new homeModuleApplet(NULL, skinner);
	appletWidget->setSkinner(skinner);

	// When signal from applet is recieved (button clicked)
	// call activateWidget().
	connect(appletWidget, SIGNAL(buttonClicked()), this, SLOT(activateWidget()));

	return appletWidget;
}


Q_EXPORT_PLUGIN2(home, homeModule);
