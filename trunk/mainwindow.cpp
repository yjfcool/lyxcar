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
#include "home.h"

AMainWindow::AMainWindow(QWidget *parent) : QMainWindow(parent, Qt::Dialog) {
	setFixedSize(800, 600);

	skinner = new ASkinner(this, "default");

	QWidget *mainWidget = new QWidget(this);
	QVBoxLayout *layout = new QVBoxLayout(mainWidget);
	layout->setSpacing(0);
	layout->setMargin(0);
	mainWidget->setLayout(layout);

	setCentralWidget(mainWidget);

	panel = new APanel(mainWidget, skinner);

	QPalette pal = palette();
	QPixmap bgImg(skinner->skinImage("", "", "background"));
	QBrush brush = QBrush();
	brush.setTexture(bgImg);
	pal.setBrush(QPalette::Window, brush);

	mainArea = new QWidget();
	mainArea->setLayout(new QVBoxLayout());
	mainArea->setPalette(pal);
	mainArea->setAutoFillBackground(true);

	qobject_cast<QBoxLayout *>(mainWidget->layout())->insertWidget(0, panel);
	qobject_cast<QBoxLayout *>(mainWidget->layout())->insertWidget(0, mainArea, 1);
	qobject_cast<QBoxLayout *>(mainArea->layout())->insertSpacing(0, 64);

	// Home button
	homeBtn = new ALyxButton();
	homeBtn->setUpPixmap(QPixmap("skins/default/button_66x70.png"));
	homeBtn->setDownPixmap(QPixmap("skins/default/button_66x70.png"));
	((QBoxLayout*)panel->layout())->insertWidget(0, homeBtn, Qt::AlignCenter);
	((QBoxLayout*)panel->layout())->insertSpacing(1, 10);

	connect(homeBtn, SIGNAL(clicked()), this, SLOT(goHome()));

	ALyxHome *home = new ALyxHome();
	((QBoxLayout*)mainArea->layout())->addWidget(home);

	connect(panel, SIGNAL(repaintModuleArea()), mainArea, SLOT(repaint()));

	// Load modules from configuration file
	QSettings *modules_conf = new QSettings("conf/modules.conf", QSettings::IniFormat);
	modulesList = modules_conf->childGroups();
	// Then load all modules into QHash - create objects
	foreach (QString mod, modulesList) {
		loadModule(mod);
	}
	
	fillPanel();
	
	// FOR TESTING ONLY!!!
	/*m_interface = qobject_cast<M_Interface *>(modules["volctl"]);
	if(m_interface) {
		m_interface->setSkinner(skinner);
 		m_interface->activate(mainArea);
		((QBoxLayout*)panel->layout())->insertWidget(0, m_interface->activateApplet(panel));
	}

	m_interface = qobject_cast<M_Interface *>(modules["mp3player"]);
	if(m_interface) {
		m_interface->setSkinner(skinner);
 		m_interface->activate(mainArea);
		((QBoxLayout*)panel->layout())->insertWidget(0, m_interface->activateApplet(panel));
	}*/
	// \FOR TESTING ONLY!!!
}

AMainWindow::~AMainWindow() {

}

void AMainWindow::goHome() {
	qDebug() << "Going home!";
}

bool AMainWindow::fillPanel() {
	foreach (QString moduleName, modules.keys()) {
		M_Interface *m_int = qobject_cast<M_Interface *>(modules[moduleName]);
		m_int->setSkinner(skinner);
		QWidget *applet = m_int->activateApplet(panel);
		if(applet) {
			((QBoxLayout*)panel->layout())->insertWidget(2, applet);
			qDebug() << "Module" << moduleName << " added applet to panel";
		} else {
			qDebug() << "Module" << moduleName << "has no applet functionality";
		}
	}
	return false;
}

bool AMainWindow::loadModule(QString moduleName) {
	QDir pluginDirectory("modules/"+moduleName);

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
		modules[moduleName] = plugin;
	} else {
	    qDebug() << "Plugin not loaded" << pluginDirectory.absoluteFilePath(fileName) << pluginLoader.errorString();
	}
	return false;
} 
