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

/*
 * Works with database of mp3 files. The db stores tags and file paths to make it faster.
 */
mp3playerDatabase::mp3playerDatabase(QObject *parent) {
	m_db = QSqlDatabase::addDatabase("QSQLITE");
	m_db.setDatabaseName(QDir::toNativeSeparators(QDir::homePath()+"/data.sqlite"));
	bool ok = m_db.open();
	if(!ok) { 
	    qDebug() << "mp3player: Can't open database of media files!";
	    m_db_ok = false;
	    return;
	} else {
	    qDebug() << "mp3player: Using sqlite database. It's ok!";
	    QSqlQuery query(m_db);
	    if(!query.exec("select * from tracks limit 1;")) {
	        qDebug() << "Trying to create table.";

		QFile file("./conf/mp3player.sql");
	        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;
		QString q;
    	        while (!file.atEnd()) { q += file.readLine(); }
		if(!query.exec(q)) {
		    qDebug() << "mp3player: Tried to create table in database but failed. Won't use sqlite!";
		    m_db_ok = false;
		} else {
		    qDebug() << "mp3player: Database successfully created!";
		    m_db_ok = true;
	        }
	    }
	}
}

mp3playerDatabase::~mp3playerDatabase() {
    m_db.close();
}

/*
 * Adds a track to DB
 */
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

/*
 * When track already exists in DB but some tag fields are have been changed updates them.
 */
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

/*
 * Checks if the track data record exists in db
 */
bool mp3playerDatabase::ifExists(QString fileName) {
    QSqlQuery query(m_db);
    fileName = fileName.replace("'", "\\'");
    QString q = QString("select filename from tracks where filename = '%1' limit 1;").arg(fileName);
    qDebug() << "Query is" << q;
    if(!query.exec(q)) {
	qDebug() << "mp3player: Database track existance check failed!";
	return false;
    } else {
	if(query.first()) {
	    qDebug() << "File" << fileName << "found in database!";
	    return true;
	} else {
	    qDebug() << "File" << fileName << "NOT found in database!";
	    return false;
	}
    }
}

/*
 * Gets track information.
 */
ATrackData mp3playerDatabase::getTrack(QString fileName) {
    ATrackData td;
    td.artist = "Unknown";
    td.album = "Unknown";
    td.trackName = fileName;

    QSqlQuery query(m_db);
    QString q = QString("select filename, artist, album, trackname from tracks where filename = '%1' limit 1;").arg(fileName);
    if(!query.exec(q)) {
	qDebug() << "mp3player: Database track existance check failed!";
    } else {
	if(query.first()) {    
	    td.artist = query.value(1).toString();
	    td.album = query.value(2).toString();
	    td.trackName = query.value(3).toString();
	}
    }
    return td;
}
