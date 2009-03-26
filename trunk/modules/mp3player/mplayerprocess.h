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

#ifndef __MPLAYERPROCESS_H__
#define __MPLAYERPROCESS_H__

#include <QString>
#include <QProcess>

class MPlayerProcess : public QProcess {
	Q_OBJECT

		MPlayerProcess(QObject *parent = 0);

	signals:
		void lineAvailable(QString line);

	public slots:
		void parseLine(QByteArray ba) {}
		void processFinished(int exitCode, QProcess::ExitStatus exitStatus) {}

		bool play();

	private:
		int	mediaType;
		QString mediaFile;
		QString mediaName;
		QString mediaArtist;
		QString mediaAlbum;
//		QTime	mediaDuration;
};

#endif
