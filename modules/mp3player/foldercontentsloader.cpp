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

#include "foldercontentsloader.h"

void FolderContentsLoader::setFolder(QString folder) {
	m_folder = folder;
}

void FolderContentsLoader::run() {
	qDebug() << "Media loader started at" << m_folder;
	QDirIterator it(m_folder, QDirIterator::Subdirectories);
	while (it.hasNext()) {
		QString fullFilePath = it.next();
		if((it.fileInfo().suffix() == "mp3") ||
		(it.fileInfo().suffix() == "ogg") ||
		(it.fileInfo().suffix() == "flac")) {
//			qDebug() << "Found file" << fullFilePath;
			emit fileFound(fullFilePath);
		}
	}
}
