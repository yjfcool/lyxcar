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

	// Create main widget background palette
	QPalette pal = palette();
	QPixmap bgImg(skinner->skinImage("", "", "background"));
	QBrush brush = QBrush();
	brush.setTexture(bgImg);
	pal.setBrush(QPalette::Window, brush);

	QWidget *mainWidget = new QWidget(this);
	QVBoxLayout *layout = new QVBoxLayout(mainWidget);
	layout->setSpacing(0);
	layout->setMargin(0);
	mainWidget->setLayout(layout);
	mainWidget->setPalette(pal);
	mainWidget->setAutoFillBackground(true);

	setCentralWidget(mainWidget);

	panel = new APanel(mainWidget, skinner);
	mainArea = new QWidget();
	
	qobject_cast<QBoxLayout *>(mainWidget->layout())->addSpacing(64); // Space for header
	qobject_cast<QBoxLayout *>(mainWidget->layout())->insertWidget(1, mainArea, 1);
	qobject_cast<QBoxLayout *>(mainWidget->layout())->insertWidget(2, panel);

	// Home button
	homeBtn = new ALyxButton();
	homeBtn->setUpPixmap(QPixmap("skins/default/button_66x70.png"));
	homeBtn->setDownPixmap(QPixmap("skins/default/button_66x70.png"));
	((QBoxLayout*)panel->layout())->insertWidget(0, homeBtn, Qt::AlignCenter);
	((QBoxLayout*)panel->layout())->insertSpacing(1, 10);
	connect(homeBtn, SIGNAL(clicked()), this, SLOT(goHome()));

	// Home widget (create only)
	m_homeWidget = new ALyxHome();

	// Load modules from configuration file
	QSettings *modules_conf = new QSettings("conf/modules.conf", QSettings::IniFormat);
	modulesList = modules_conf->childGroups();
	// Then load all modules into QHash - create objects
	foreach (QString mod, modulesList) {
		loadModule(mod);
	}
	
	fillPanel();
	
	// FOR TESTING ONLY!!!
	
	//connect(panel, SIGNAL(repaintModuleArea()), mainArea, SLOT(repaint()));

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
	if(activeModuleName() != "home") {
		qDebug() << "Going home...";
		m_activeModuleName = "home";

		clearMainArea(); // Clearing
		mainArea->setLayout(new QVBoxLayout());
		((QBoxLayout*)mainArea->layout())->addWidget(homeWidget());
	} else {
		qDebug() << "Already at home!..";
	}
}

void AMainWindow::activateModule(QString moduleName) {
	if(activeModuleName() != moduleName) {
		qDebug() << "Activating module"	<< moduleName;
		m_activeModuleName = moduleName;

		clearMainArea(); // Clearing
	} else {
		qDebug() << "Already activated" << moduleName;
	}
}

void AMainWindow::clearMainArea() {
		// We need to destroy boxLayout to clear main area and create it again.
		if(mainArea->layout()) {
			qDebug() << "Clearing main area's layout";
			mainArea->layout()->destroy();
		}
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
