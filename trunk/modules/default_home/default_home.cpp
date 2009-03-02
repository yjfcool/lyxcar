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

#include "default_home.h"

/*
 * Widget class implementation
*/

homeModuleWidget::homeModuleWidget(QWidget *parent, ASkinner *s) {
	m_skinner = s;

	// Construct menus from a skin defenition
	QDomElement buttonsElement = m_skinner->skinModuleElement("default_home", "buttons");
	QDomNodeList buttonsList = buttonsElement.elementsByTagName("button");
	for(int i = 0; i < buttonsList.count(); i++) {
		QDomElement buttonElement = buttonsList.at(i).toElement();
		if(!buttonElement.isNull()) {
			int tmp_at = 0;

			// Get button properties
			QString bname = buttonElement.attribute("name");
			QString value = buttonElement.attribute("value");
			QString pressed = buttonElement.attribute("pressed");
			QString released = buttonElement.attribute("released");
			qDebug() << bname << value << pressed << released;

			// Append button to the buttons list,
			// and create animation object for button.
			buttons[bname] = new ALyxButton(this);
			buttons[bname]->setObjectName(bname);
			buttons[bname]->setUpPixmap(QPixmap(m_skinner->skinModuleImagePath("default_home")+released));
			buttons[bname]->setDownPixmap(QPixmap(m_skinner->skinModuleImagePath("default_home")+pressed));

			// Connect button to a module activation slot
			// ONLY NOW BY DEFAULT, WE NEED TO CHANGE THIS IF
			// WE HAVE BUTTON FUNCTIONS OTHER THAN JUST CALLING
			// MODULES!
			connect(buttons[bname], SIGNAL(clicked()), this, SLOT(activateModule()));

			// Get button animations
			QDomElement animationElement = buttonElement.firstChildElement("animation");
			if(!animationElement.isNull()) {
				QDomNodeList stopsList = animationElement.elementsByTagName("stop");
				animations[bname] = new ALyxAnimation(this, buttons[bname]);
				animations[bname]->setAnimationTime(animationElement.attribute("time").toInt());
				// Detect the longest animation queue
				if(tmp_at < animationElement.attribute("time").toInt()) { tmp_at = animationElement.attribute("time").toInt(); lastAnimation = animations[bname]; }
				for(int a = 0; a < stopsList.count(); a++) {
					QDomElement stopElement = stopsList.at(a).toElement();
					if(!stopElement.isNull()) {
						int time = stopElement.attribute("time").toInt();
						int x = stopElement.attribute("x").toInt();
						int y = stopElement.attribute("y").toInt();
						int width = stopElement.attribute("width").toInt();
						int height = stopElement.attribute("height").toInt();
						float opacity = stopElement.attribute("opacity").toFloat();
						int acceleration = stopElement.attribute("acceleration").toInt();
						animations[bname]->stops << ALyxAnimationStop(time, x, y, width, height, opacity);
						qDebug() << bname << "stop at" << time << x << y << width << height << opacity;
					}
				}       
			} else {
				// Get button position and rectangle
				QDomElement rectElement = buttonElement.firstChildElement("rect");
				if(!rectElement.isNull()) {
					int ini_x = rectElement.attribute("x").toInt();
					int ini_y = rectElement.attribute("y").toInt();
					int ini_width = rectElement.attribute("width").toInt();
					int ini_height = rectElement.attribute("height").toInt();
					buttons[bname]->move(ini_x, ini_y);
					buttons[bname]->setFixedSize(ini_width, ini_height);
				} else {
				 	qDebug() << "Warning: no initial rectangle for" << bname << "defined";
				}
			}
		}
	}

	foreach (QString anim, animations.keys()) {
		animations[anim]->start();
	}
}

void homeModuleWidget::animateReverse() {
	if(animations.count() > 0) {
		// If there is any animation object, connect the fin of it to animationFinished signal.
		// Only for reverse animation which means deactivation of a module widget.
		if(lastAnimation) {
			connect(lastAnimation, SIGNAL(finished()), this, SIGNAL(animationFinished()));
		}
		foreach (QString anim, animations.keys()) {
			animations[anim]->reverse();
		}
	}
}

homeModuleWidget::~homeModuleWidget() {
	qDebug() << "homeModuleWidget destroyed";	
}

/* SLOT
 * We use this function when we need to activate another module from current module.
 * The name of module to be activated is defined by objectName of a caller.
 * For example, if we have a button called "foo", and associated with module "bar"
 * we need to use substitution table to access "bar".
*/
void homeModuleWidget::activateModule() {
	qDebug() << "activateModule recieved objectName" << sender()->objectName();

	emit activateClicked(sender()->objectName());
}
	
/*
 * Applet class implementation
*/
homeModuleApplet::homeModuleApplet(QWidget *parent, ASkinner *s) {
	m_skinner = s;

	// This is a simple home button
	ALyxButton *button = new ALyxButton(this);
	button->setUpPixmap(QPixmap(m_skinner->skinModuleImage("default_home", "button", "released")));
	button->setDownPixmap(QPixmap(m_skinner->skinModuleImage("default_home", "button", "pressed")));

	setFixedWidth(button->width());

	// When the button is clicked emit signal from an applet
	connect(button, SIGNAL(clicked()), this, SIGNAL(buttonClicked()));

}

homeModuleApplet::~homeModuleApplet() {
	qDebug() << "homeModuleApplet destroyed";
}

QWidget *homeModule::activate(QWidget *parent) {
	moduleWidget = new homeModuleWidget(parent, m_skinner);

	connect(moduleWidget, SIGNAL(activateClicked(QString)), this, SLOT(activateModuleWidget(QString)));

	return moduleWidget;
}

void homeModule::deactivate(QString deactivateFor) {
	qDebug() << "Deactivating current widget. The next module is" << deactivateFor;

	// It's needed to pass net module name to properly deactivate this and activate next module!
	nextModuleName = deactivateFor;
	connect(moduleWidget, SIGNAL(animationFinished()), this, SLOT(deactivationFinished()));
	moduleWidget->animateReverse();
}

void homeModule::deactivationFinished() {
	emit deactivated(nextModuleName);
}

QWidget *homeModule::activateApplet(QWidget *parent) {
	qDebug() << "Appending default_home plugin to panel";

	// Create applet widget
	appletWidget = new homeModuleApplet(NULL, m_skinner);
	appletWidget->setSkinner(m_skinner);

	// When signal from applet is recieved (button clicked)
	// call activateWidget().
	connect(appletWidget, SIGNAL(buttonClicked()), this, SLOT(activateMyself()));

	return appletWidget;
}


Q_EXPORT_PLUGIN2(home, homeModule);
