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

#include "skinner.h"

ASkinner::ASkinner(QObject *parent) {
	skin = new QDomDocument();
}

//
// @brief Create a skin object and load skin specified by skinName.
//
ASkinner::ASkinner(QObject *parent, QString name) {
	skin = new QDomDocument();
	if(loadSkin(name) > 0) {
		// Skin load error
		QApplication::exit(1);
	}
}

int ASkinner::loadSkin(QString name) {
	skinName = name;

	// Load skin configuration file
	QFile file("../skins/"+skinName+"/"+skinName+".xml");
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

		QString attr = "../skins/"+skinName+"/"+skinRoot.attribute(attribute);
		qDebug() << "Loaded skin root attribute: " << attr;
		return attr;

	} else if(root == "panel") {

		QString attr = "../skins/"+skinName+"/"+panel.attribute(attribute);
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
			QString attr = "../skins/"+skinName+"/"+module+"/"+objectRoot.attribute(attribute);
			qDebug() << "Loaded skin attribute: " << attr;
			printf(attr.toAscii());
			return attr;
		}
	}

	return QString("");
}
