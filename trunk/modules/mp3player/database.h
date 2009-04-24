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

#ifndef __DATABASE_H__
#define __DATABASE_H__

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>

#include <QObject>
#include <QDebug>
#include <QStringList>
#include <QtCore>

class mp3playerDatabase : public QObject {
    Q_OBJECT
    public:
	mp3playerDatabase(QObject *parent = 0);
	~mp3playerDatabase();

	void addTrack(QString fileName, QString artist, QString album, QString trackName, QString duration);
	void updateTrack(QString fileName, QString artist, QString album, QString trackName, QString duration);
	bool ifExists(QString fileName);
	void removeTrack(QString file) {}
	void updateDir(QDir directory) {}
	void rescan() {}

	QString getFileName(QString artist, QString album, QString trackName) { return QString(); }
	QString getArtistByFile(QString file) { return QString(); }
	QString getArtistByTrack(QString album, QString trackName) { return QString(); }
	QStringList getTracksList(QString artist, QString album) { return QStringList(); }

	bool isOK() { return m_db_ok; }

    private:
	QSqlDatabase m_db;
	bool m_db_ok;
};

#endif // __DATABASE_H__
