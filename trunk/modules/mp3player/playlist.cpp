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

#ifdef Q_OS_WIN32
	tagCodec = QTextCodec::codecForName("Windows-1251");
#endif

}

void APlaylist::addEntry(QString filePath, QString fileName, QString artist, QString album, QString title) {
	if(!filePath.isEmpty() && !fileName.isEmpty()) {
		if(!QFile::exists(filePath+"/"+fileName)) {
			qDebug() << "No such a file:" << filePath+"/"+fileName << "!";
			return;
		}
		QDomElement tag = m_xml.createElement("entry");
		tag.setAttribute("filePath", filePath);
		tag.setAttribute("fileName", fileName);

		parseTags(&tag);

		m_root.appendChild(tag);

		emit entryAdded(title, album, artist);
	} else {
		qDebug() << "FilePath or fileName is empty! Can't add.";
	}
}

void APlaylist::parseTags(QDomElement *entry) {
		QString artist, album, title;

		artist = entry->attribute("artist");
		album = entry->attribute("album");
		title = entry->attribute("title");

		// Parse mp3 tags during entry adding
		QString t_fileName = (entry->attribute("filePath")+"/"+entry->attribute("fileName")).toLocal8Bit();
		TagLib::FileRef f(t_fileName.toAscii().constData());
		if(artist.isEmpty()) artist = TStringToQString(f.tag()->artist());
		if(album.isEmpty()) album = TStringToQString(f.tag()->album());
		if(title.isEmpty()) title = TStringToQString(f.tag()->title());

// For Russian windows users whose tags are in cp-1251
#ifdef Q_OS_WIN32
		artist = tagCodec->toUnicode(artist.toAscii());
		album = tagCodec->toUnicode(album.toAscii());
		title = tagCodec->toUnicode(title.toAscii());
#endif

		entry->setAttribute("album", album);
		entry->setAttribute("artist", artist);
		entry->setAttribute("title", title);

		qDebug() << "Tags set to" << artist << album << title;
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
