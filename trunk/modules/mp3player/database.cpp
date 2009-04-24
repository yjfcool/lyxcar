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

#include "database.h"

mp3playerDatabase::mp3playerDatabase(QObject *parent) {
	m_db = QSqlDatabase::addDatabase("QSQLITE");
	m_db.setDatabaseName(QDir::toNativeSeparators(QDir::homePath()+"/data.sqlite"));
	bool ok = m_db.open();
	if(!ok) { 
	    qDebug() << "mp3player: Can't open database of media files!";
	    return;
	} else {
	    qDebug() << "mp3player: Using sqlite database. It's ok!";
	    m_db_ok = true;
	}
}

mp3playerDatabase::~mp3playerDatabase() {
    m_db.close();
}

void mp3playerDatabase::addTrack(
    QString fileName,
    QString artist, 
    QString album, 
    QString trackName, 
    QString duration) {
    QSqlQuery query(m_db);
    
    query.prepare("insert into tracks (filename, artist, album, trackname, duration) values (:fileName, :artist, :album, :trackName, :duration);");
    query.bindValue(":fileName", fileName);
    query.bindValue(":artist", artist);
    query.bindValue(":album", album);
    query.bindValue(":trackName", trackName);
    query.bindValue(":duration", duration);
    if(!query.exec()) {
	qDebug() << "mp3player: Can't add a track" << fileName << "to database!";
    }
}

void mp3playerDatabase::updateTrack(
    QString fileName,
    QString artist,
    QString album,
    QString trackName,
    QString duration) {
    QSqlQuery query(m_db);
    
    query.prepare("update tracks set artist = :artist, album = :album, trackname = :trackName, duration = :duration where filename = :fileName;");
    query.bindValue(":fileName", fileName);
    query.bindValue(":artist", artist);
    query.bindValue(":album", album);
    query.bindValue(":trackName", trackName);
    query.bindValue(":duration", duration);
    if(!query.exec()) {
	qDebug() << "mp3player: Can't update track" << fileName << "to database!";
    }
}

bool mp3playerDatabase::ifExists(QString fileName) {
    QSqlQuery query(m_db);
    QString q = QString("select filename from tracks where filename = %1").arg(fileName);
    if(!query.exec(q)) {
	qDebug() << "mp3player: Database track existance check failed!";
    }
    if(query.size() > 0) {
	return true;
    } else {
	return false;
    }
}
