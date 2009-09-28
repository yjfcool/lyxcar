/*
 * Copyright (C) 2008-2009 Pavlov Denis
 *
 * Comments unavailable.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or any later version.
 *
*/

#include "playlist.h"

#include <QDebug>

APlaylist::APlaylist(QString fileName) {
	m_xml = QDomDocument("playlist");
	m_root = m_xml.createElement("playlist");
	m_xml.appendChild(m_root);

	m_fileName = fileName;
}

void APlaylist::addEntry(QString filePath, QString fileName, QString artist, QString album, QString title) {
	if(!filePath.isEmpty() && !fileName.isEmpty()) {
		QDomElement tag = m_xml.createElement("entry");
		tag.setAttribute("filePath", filePath);
		tag.setAttribute("fileName", fileName);

		tag.setAttribute("album", album);
		tag.setAttribute("artist", artist);
		tag.setAttribute("title", title);

		m_root.appendChild(tag);

		emit entryAdded(title, album, artist);
	} else {
		qDebug() << "FilePath or fileName is empty! Can't add.";
	}
}

void APlaylist::addDir(QString dirName) {

}

void APlaylist::addDir(QDir dir) {

}

void APlaylist::removeEntries(QString filePath, QString fileName) {

}

void APlaylist::load(QString fileName) {
	if(fileName.isEmpty()) { fileName = m_fileName; } else { m_fileName = fileName; }
	QFile file(fileName);
	if(!file.open(QIODevice::ReadOnly)) {
		qDebug() << "File open error:" << fileName << "!";
		return;
	}
	if(!m_xml.setContent(&file)) {
		qDebug() << "Can't load file:" << fileName << "!";
		file.close();
		return;
	}
	emit loaded();
	file.close();
}

void APlaylist::save(QString fileName) {
	if(fileName.isEmpty()) { fileName = m_fileName; } else { m_fileName = fileName; }
	QString playListInText = m_xml.toString();

	QFile file(fileName);
	if(!file.open(QIODevice::WriteOnly)) {
		qDebug() << "Can't save file:" << fileName << "!";
		return;
	}

	QTextStream out(&file);
	out << playListInText;

	file.close();
}

void APlaylist::clear() {
	emit cleared();
}
