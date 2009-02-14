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
#include "lists.h"

AMainWindow::AMainWindow(QWidget *parent) {
	resize(800, 600);

	skinner = new ASkinner(this, "default");

	QWidget *mainWidget = new QWidget(this);
	QVBoxLayout *layout = new QVBoxLayout(mainWidget);
	layout->setSpacing(0);
	layout->setMargin(0);
	mainWidget->setLayout(layout);

	setCentralWidget(mainWidget);

	panel = new APanel(mainWidget, skinner);

	mainArea = new QWidget();
	mainArea->setLayout(new QVBoxLayout());

	QPalette pal = palette();
	QPixmap bgImg(skinner->skinImage("", "", "background"));
	QBrush brush = QBrush();
	brush.setTexture(bgImg);
	pal.setBrush(QPalette::Window, brush);
	mainArea->setPalette(pal);
	mainArea->setAutoFillBackground(true);

	qobject_cast<QBoxLayout *>(mainWidget->layout())->insertWidget(0, panel);
	qobject_cast<QBoxLayout *>(mainWidget->layout())->insertWidget(0, mainArea, 1);

	mainArea->setLayout(new QVBoxLayout());

	ALyxListBox *listbox = new ALyxListBox(mainArea, skinner);
	listbox->setGeometry(100, 100, 300, 200);
	qobject_cast<QBoxLayout *>(mainArea->layout())->addStretch(1);
	qobject_cast<QBoxLayout *>(mainArea->layout())->addWidget(listbox, 1);
	
	connect(panel, SIGNAL(repaintModuleArea()), mainArea, SLOT(repaint()));

	loadPlugin();
}

AMainWindow::~AMainWindow() {

}

bool AMainWindow::loadPlugin() {
	QDir pluginDirectory("modules/volctl");

#ifdef Q_OS_WIN32
	qDebug() << "Loading Windows plugins";
	QString fileName = pluginDirectory.entryList(QStringList() << "*.dll").first();
#endif

#ifdef Q_OS_UNIX
	qDebug() << "Loading Unix plugins";
	QString fileName = pluginDirectory.entryList(QStringList() << "*.so").first();
#endif

	QPluginLoader pluginLoader(pluginDirectory.absoluteFilePath(fileName));
	QObject *plugin = pluginLoader.instance();
	qDebug() << "Trying plugin" << pluginDirectory.absoluteFilePath(fileName);

	if (plugin != NULL) {
		qDebug() << "Discovered plugin" << fileName;
		m_interface = qobject_cast<M_Interface *>(plugin);
		if(m_interface) {
			m_interface->setSkinner(skinner);
               		m_interface->activate(mainArea);
               		m_interface->appendToPanel(panel, 0);
			return true;
		}
	} else {
	    qDebug() << "Plugin not loaded" << pluginDirectory.absoluteFilePath(fileName) << pluginLoader.errorString();
	}
	return false;
} 
