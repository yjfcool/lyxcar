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

#ifndef _PLAYLIST_H_
#define _PLAYLIST_H_

#include <QDomDocument>
#include <QFile>
#include <QDir>

#include <taglib.h>
#include <fileref.h>
#include <tag.h>
#include <id3v1tag.h>
#include <id3v2tag.h>
#include <tstring.h>

class APlaylist : public QObject
{
	Q_OBJECT
public:
	APlaylist(QString fileName);

	QString		m_fileName;
	QDomElement	m_root;

	QDomDocument	m_xml;

	void	addEntry(QString filePath, QString fileName, QString artist = "", QString album = "", QString title = "");
	void	setEntryArtist(QString filePath, QString fileName, QString artist) {}
	void	setEntryAlbum(QString filePath, QString fileName, QString album) {}
	void	setEntryTitle(QString filePath, QString fileName, QString title) {}
	void	updateEntry(QString filePath, QString fileName) {}

	void	addDir(QString dirName);
	void	addDir(QDir dir);
	void	removeEntries(QString filePath, QString fileName);

	void	load(QString fileName = "");
	void	save(QString fileName = "");
	void	clear();

signals:
	void	loaded();
	void	cleared();
	void	entryAdded(QString title, QString album, QString artist);
};

#endif // _PLAYLIST_H_
