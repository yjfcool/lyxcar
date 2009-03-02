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

#include <QMessageBox>

#include "skinner.h"

ASkinner::ASkinner(QObject *parent, QString name) {
	skin = new QDomDocument();
	if(loadSkin(name) > 0) {
		// Skin load error
		QMessageBox::critical(0, tr("Skin load error"), tr("LyxCar cannot load skin."));
		QApplication::exit(1);
	}
}

int ASkinner::loadSkin(QString name) {
	skinName = name;

	// Load skin configuration file
	QFile file("./skins/"+skinName+"/"+skinName+".xml");
	if(!file.open(QIODevice::ReadOnly))
		return 1;

	if(!skin->setContent(&file)) {
 		file.close();
		return 1;
	}

	file.close();

	skinRoot = skin->documentElement();
	panel = skinRoot.firstChildElement("panel");
	modules = skinRoot.firstChildElement("modules");

	return 0; // Return 1 if loading error
}

QString ASkinner::skinValue(QString part, QString root, QString attribute) {
	if(((root == "") || (root == "root")) && (part == "")) {

		QString attr = skinRoot.attribute(attribute);
		qDebug() << "Loaded skin root attribute: " << attr;
		return attr;

	} else if(root == "panel") {

		QString attr = panel.attribute(attribute);
		qDebug() << "Loaded skin panel attribute: " << attr;
		return attr;

	}

	return QString("");
}

QString ASkinner::skinModuleValue(QString module, QString object, QString attribute) {
	QDomElement moduleRoot = modules.firstChildElement(module);
	if(!moduleRoot.isNull()) {
		QDomElement objectRoot = moduleRoot.firstChildElement(object);
		if(!objectRoot.isNull()) {
			QString attr = objectRoot.attribute(attribute);
			qDebug() << "Loaded skin attribute: " << attr;
			return attr;
		}
	}

	return QString("");
}

QDomElement ASkinner::skinModuleElement(QString module, QString elementName) {
	QDomElement moduleRoot = modules.firstChildElement(module);
	if(!moduleRoot.isNull()) {
		QDomElement objectRoot = moduleRoot.firstChildElement(elementName);
		if(!objectRoot.isNull()) {
			qDebug() << "Loaded skin element: " << elementName;
			return objectRoot;
		} else {
			qDebug() << "No such element in module" << module << "skin defenition:" << elementName;
			return QDomElement();
		}
	} else {
		return QDomElement();
	}
}

QDomElement ASkinner::skinModuleElementByName(QString module, QString element, QString elementName) {
	QDomElement moduleRoot = modules.firstChildElement(module);
	if(!moduleRoot.isNull()) {
		QDomElement objectRoot;
		QDomNodeList list = moduleRoot.elementsByTagName(element);
		for(int i = 0; i < list.count(); i++) {
			if(list.item(i).toElement().attribute("name") == elementName) {
				objectRoot = list.item(i).toElement();
			}
		}
		if(!objectRoot.isNull()) {
			qDebug() << "Loaded skin element: " << elementName;
			return objectRoot;
		} else {
			qDebug() << "ERROR: No such element in module" << module << "skin defenition:" << elementName;
			return QDomElement();
		}
	} else {
		qDebug() << "ERROR: No configuration for" << module << "in this skin!";
		return QDomElement();
	}
}

QString ASkinner::skinModuleImage(QString module, QString object, QString attribute) {
	QString attr = "./skins/"+skinName+"/"+module+"/"+skinModuleValue(module, object, attribute);;
	return attr;
}

QString ASkinner::skinImage(QString part, QString root, QString attribute) {
	QString attr = "./skins/"+skinName+"/"+skinValue(part, root, attribute);;
	return attr;
}

QString ASkinner::skinModuleImagePath(QString module) {
	QString path = "./skins/"+skinName+"/"+module+"/";
	return path;
}
