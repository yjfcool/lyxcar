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

AMainWindow::AMainWindow(QWidget *parent) :
   QMainWindow(parent)
{
   init("default");
}

AMainWindow::AMainWindow(const QString & skinName, QWidget * parent) :
   QMainWindow(parent)
{
   init(skinName);
}

AMainWindow::~AMainWindow()
{
}

/*
 * This function activates modules:
 * 1) If there is a loaded and activated module we need to deactivate it.
 * 1.1) Connect it's deactivated(QString) signal to new module activateModule(QString) slot.
 * 1.2) Call deactivate() for it.
 * 2) If there isn't any module activated then just activate a new module.
 */
void AMainWindow::activateModuleDemand(QString moduleName) {
	if(activeModuleName() != moduleName) {
		qDebug() << "MainWidget says Got activateModuleDemand(" << moduleName << ")";
		// Get current active module
		M_Interface *prevModule = qobject_cast<M_Interface *>(modules[m_activeModuleName]);
		qDebug() << "MainWidget says Interface created for" << moduleName;

		// Connect module activated signal to ...
		// Connect module deactivated signal to activateModule(...)
		if(prevModule) {
			QString deactivateFor = moduleName; // Means "deactivate previous module and activate moduleName".
		        connect(modules[m_activeModuleName], SIGNAL(deactivated(QString)), this, SLOT(activateModule(QString)));
			qDebug() << "MainWidget says deactivated() signal connected for module" << m_activeModuleName;
			qDebug() << "MainWidget says sending deactivation call for module" << prevModule->moduleName();
			prevModule->deactivate(deactivateFor);
		} else {
			activateModule(moduleName);
		}
	} else {
		qDebug() << "Warning: Already activated" << moduleName;
	}
}

void AMainWindow::activateModule(QString moduleName) {
	qDebug() << "MainWidget says that deactivated() was recieved if it was possible. Activating" << moduleName;
	clearMainArea(); // Clearing

	// Activate module by moduleName.
	m_interface = qobject_cast<M_Interface *>(modules[moduleName]);
	if(m_interface) {
		// Assume if there is module activated it has been connected to deactivation slot!
		if(modules[m_activeModuleName]) {
			qDebug() << "MainWidget says deactivated() signal disconnected from" << m_activeModuleName;
			disconnect(modules[m_activeModuleName], SIGNAL(deactivated(QString)), this, SLOT(activateModule(QString)));
		}
		m_activeModuleName = moduleName;
		mainArea->setLayout(new QVBoxLayout(mainArea));
		((QBoxLayout*)mainArea->layout())->setContentsMargins(0, 0, 0, 0);
		((QBoxLayout*)mainArea->layout())->setMargin(0);
		((QBoxLayout*)mainArea->layout())->setSpacing(0);
		qDebug() << "skinner object set for" << moduleName;
		m_interface->setSkinner(skinner);
		qDebug() << "activate() for" << moduleName << "called";
		((QBoxLayout*)mainArea->layout())->addWidget(m_interface->activate(mainArea));
	} else {
		qDebug() << "Error: Can't activate" << moduleName << "because module object is NULL!";
	}
}

void AMainWindow::replyActivation(QString mname) {
	qDebug() << "MainWidget says Replying activation demandance from" << mname;
	activateModuleDemand(mname);
}

void AMainWindow::clearMainArea() { // ** UNFinished **
		// We need to destroy boxLayout to clear main area and create it again.
		if(mainArea->layout()) {
			qDebug() << "MainWidget says clearing main area's layout: mainArea->layout() destroyed";
			foreach(QObject *child, mainArea->children()) {
				// Hide all QWidget elements and delete all other!
				if(child->inherits("QWidget")) {
					qDebug() << "Hiding" << child->objectName();
					qobject_cast<QWidget *>(child)->hide();
				} else {
					qDebug() << "Deleting" << child->objectName();
					child->deleteLater();
				}
			}
			// CHECK IF the garbage collector destroys module widget?!
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
			qDebug() << "MainWidget says Module" << moduleName << " added applet to panel";
		} else {
			qDebug() << "MainWidget says Module" << moduleName << "has no applet functionality";
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
	qDebug() << "MainWidget says Trying plugin" << pluginDirectory.absoluteFilePath(fileName);

	if (plugin != NULL) {
		qDebug() << "MainWidget says Discovered plugin" << fileName;
		modules[moduleName] = plugin;
		qobject_cast<M_Interface *>(plugin)->setModuleName(moduleName);
		qobject_cast<M_Interface *>(plugin)->setAudioOutput(m_audioOutput);

		// Connect module's activation demand signal
		// to main window reply slot.
		connect(plugin, SIGNAL(demandActivation(QString)), this, SLOT(replyActivation(QString)));
	} else {
	    qDebug() << "MainWidget says Plugin not loaded" << pluginDirectory.absoluteFilePath(fileName) << pluginLoader.errorString();
	}
	return false;
} 
   
void AMainWindow::init(const QString & skin_name)
{
   QString defaultModule;

   skinner = new ASkinner(this, skin_name);
   
   int headerSpace = skinner->skinValue("", "", "header_space").toInt();
   int width = skinner->skinValue("", "", "width").toInt();
   int height = skinner->skinValue("", "", "height").toInt();
   setFixedSize(width, height);

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
   layout->setContentsMargins(0,0,0,0);
   mainWidget->setLayout(layout);
   mainWidget->setPalette(pal);
   mainWidget->setAutoFillBackground(true);

   setCentralWidget(mainWidget);

   panel = new APanel(mainWidget, skinner);
   mainArea = new QWidget();

   qobject_cast<QBoxLayout *>(mainWidget->layout())->addSpacing(headerSpace); // Space for header
   qobject_cast<QBoxLayout *>(mainWidget->layout())->insertWidget(1, mainArea, 1);
   qobject_cast<QBoxLayout *>(mainWidget->layout())->insertWidget(2, panel);

    // Load modules from configuration file
    QSettings *modules_conf = new QSettings("conf/modules.conf", QSettings::IniFormat);
    modulesList = modules_conf->childGroups();

    // Create main audio output for main program
    m_audioOutput = new Phonon::AudioOutput(Phonon::MusicCategory, this);

    // Then load all modules into QHash - create objects
    foreach (QString mod, modulesList) 
    {
	loadModule(mod);
	if(modules_conf->value(mod+"/Default").toInt() > 0) {
	    defaultModule = mod;
	}
    }

    fillPanel();

    // Activate default module, or activate saved state module.
    activateModule(defaultModule);
}
