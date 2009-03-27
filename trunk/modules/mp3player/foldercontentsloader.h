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

#ifndef FOLDERCONTENTSLOADER_H
#define FOLDERCONTENTSLOADER_H

#include <QThread>
#include <QTextCodec>
#include <QDirIterator>

#include <QDebug>

class FolderContentsLoader : public QThread {
	Q_OBJECT
	public:
		void setFolder(QString name);
		void run();

	private:
		QTextCodec *codec;
		QDirIterator *it;

		QString m_folder;

	signals:
		void progress(int percent);
		void fileFound(QString fileName);
};

#endif // FOLDERCONTENTSLOADER_H
