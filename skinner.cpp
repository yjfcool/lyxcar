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

ASkinner::ASkinner() {
	skin = new QDomDocument();
}

//
// @brief Create a skin object and load skin specified by skinName.
//
ASkinner::ASkinner(QString name) {
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

	return 0; // Return 1 if loading error
}

QString ASkinner::skinValue(QString root, QString attribute) {
	if((root == "") || (root == "root")) {
		return "../skins/"+skinName+"/"+skinRoot.attribute(attribute);
	}

	return QString("");
}
