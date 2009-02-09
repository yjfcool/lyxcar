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

#include "mplayerprocess.h"

//Clip info
static QRegExp rx_clip_name("^ (name|title): (.*)", Qt::CaseInsensitive);
static QRegExp rx_clip_artist("^ artist: (.*)", Qt::CaseInsensitive);
static QRegExp rx_clip_author("^ author: (.*)", Qt::CaseInsensitive);
static QRegExp rx_clip_album("^ album: (.*)", Qt::CaseInsensitive);
static QRegExp rx_clip_genre("^ genre: (.*)", Qt::CaseInsensitive);
static QRegExp rx_clip_date("^ (creation date|year): (.*)", Qt::CaseInsensitive);
static QRegExp rx_clip_track("^ track: (.*)", Qt::CaseInsensitive);
static QRegExp rx_clip_copyright("^ copyright: (.*)", Qt::CaseInsensitive);
static QRegExp rx_clip_comment("^ comment: (.*)", Qt::CaseInsensitive);
static QRegExp rx_clip_software("^ software: (.*)", Qt::CaseInsensitive);

static QRegExp rx_stream_title("^.* StreamTitle='(.*)';StreamUrl='(.*)';");

MPlayerProcess::MPlayerProcess(QObject *parent) {

}

bool MPlayerProcess::play() {
	start("../mplayer/mplayer.exe", QStringList() << "-slave" << "test.mp3",
		QIODevice::ReadWrite | QIODevice::Unbuffered);

	if(!waitForStarted()) {
		return false;
	}
	return true;
}
