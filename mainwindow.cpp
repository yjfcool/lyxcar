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

#include <QPluginLoader>
#include <QApplication>
#include <QMessageBox>

#include "mainwindow.h"
#include "mainmenu.h"

AMainWindow::AMainWindow(QWidget *parent) {
	resize(800, 600);

	QWidget *mainWidget = new QWidget(this);
	QVBoxLayout *layout = new QVBoxLayout(mainWidget);
	layout->setSpacing(0);
	layout->setMargin(0);
	mainWidget->setLayout(layout);

	setCentralWidget(mainWidget);

	panel = new APanel(mainWidget);

	mainArea = new QWidget();
	mainArea->setLayout(new QVBoxLayout());

	((QBoxLayout *)mainWidget->layout())->insertWidget(0, panel);
	((QBoxLayout *)mainWidget->layout())->insertWidget(0, mainArea, 1);

	connect(panel, SIGNAL(repaintModuleArea()), mainArea, SLOT(repaint()));

	loadPlugin();
}

AMainWindow::~AMainWindow() {

}

bool AMainWindow::loadPlugin() {
	QDir pluginDirectory("../modules/volctl");
	QString fileName = pluginDirectory.entryList(QStringList() << "*.dll").first();

	QPluginLoader pluginLoader(pluginDirectory.absoluteFilePath(fileName));
	QObject *plugin = pluginLoader.instance();
	if (plugin) {
		m_interface = qobject_cast<M_Interface *>(plugin);
		if(m_interface) {
               		m_interface->activate(mainArea);
               		m_interface->appendToPanel(panel, 0);
			return true;
		}
	}
	return false;
} 
