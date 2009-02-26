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
#include <QtGlobal>

#include "mainwindow.h"
#include "mainmenu.h"
#include "lists.h"
#include "home.h"

AMainWindow::AMainWindow(QWidget *parent) {
	resize(800, 600);

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

void AMainWindow::activateModule(QString moduleName) {
	if(activeModuleName() != moduleName) {
		qDebug() << "Activating module"	<< moduleName;
		m_activeModuleName = moduleName;

		clearMainArea(); // Clearing

		// Activate module by moduleName.
		m_interface = qobject_cast<M_Interface *>(modules[moduleName]);
		if(m_interface) {
			mainArea->setLayout(new QVBoxLayout());
 			qobject_cast<QBoxLayout*>(mainArea->layout())->addWidget(m_interface->activate());
		}
	} else {
		qDebug() << "Already activated" << moduleName;
	}
}

void AMainWindow::replyActivation(QString mname) {
	qDebug() << "Replying activation demandance from" << mname;

	activateModule(mname);
}

void AMainWindow::clearMainArea() { // ** Finished **
		// We need to destroy boxLayout to clear main area and create it again.
		if(mainArea->layout()) {
			qDebug() << "Clearing main area's layout: mainArea->layout() destroyed";
			delete mainArea->layout();
		}
}

bool AMainWindow::fillPanel() { // ** Finished **
	foreach (QString moduleName, modules.keys()) {
		M_Interface *m_int = qobject_cast<M_Interface *>(modules[moduleName]);
		m_int->setSkinner(skinner);
		QWidget *applet = m_int->activateApplet(panel);
		if(applet) {
			(qobject_cast<QBoxLayout *>(panel->layout()))->insertWidget(0, applet);
			qDebug() << "Module" << moduleName << " added applet to panel";
		} else {
			qDebug() << "Module" << moduleName << "has no applet functionality";
		}
	}
	return false;
}

bool AMainWindow::loadModule(QString moduleName) { // ** Finished **
	QDir pluginDirectory("modules/"+moduleName);

   QString fileName, temporaryName;

   // module path is modules/<moduleName>/<prefix><moduleName>.<platform-specific ext>
   foreach (temporaryName, pluginDirectory.entryList(QStringList() << "*" + moduleName + ".*")) {
      // check extension
      if (QLibrary::isLibrary(temporaryName)) {
         fileName = temporaryName;
         break;
      }
   }

   if (fileName.isEmpty()) {
      return false;
   }

	QPluginLoader pluginLoader(pluginDirectory.absoluteFilePath(fileName));
	QObject *plugin = pluginLoader.instance();
	qDebug() << "Trying plugin" << pluginDirectory.absoluteFilePath(fileName);

	if (plugin != NULL) {
		qDebug() << "Discovered plugin" << fileName;
		modules[moduleName] = plugin;
		qobject_cast<M_Interface *>(plugin)->setModuleName(moduleName);

		// Connect module's activation demand signal
		// to main window reply slot.
		connect(plugin, SIGNAL(demandActivation(QString)), this, SLOT(replyActivation(QString)));
	} else {
	    qDebug() << "Plugin not loaded" << pluginDirectory.absoluteFilePath(fileName) << pluginLoader.errorString();
	}
	return false;
} 
