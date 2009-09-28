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

#include "filelist.h"

ALyxFileListWidget::ALyxFileListWidget(QWidget *parent, ASkinner *skinner) :
	ALyxListWidget(parent, skinner) {

	setRootDir("./");
}

void ALyxFileListWidget::refresh() {
	clear();
	readRootDir();
}

void ALyxFileListWidget::readRootDir() {
	unsigned int i;

	// Add first element of parent directory
	ALyxListWidgetItem *item = new ALyxListWidgetItem(this, tr("Up"));
	item->setPixmap(QPixmap("./skins/default/icons/folder.png"));
	addItem(item);

	// Read directories first
	QStringList list = m_rootdir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
	for(i = 0; i < list.count(); i++) {
		ALyxListWidgetItem *item = new ALyxListWidgetItem(this, list[i]);
		item->setPixmap(QPixmap("./skins/default/icons/folder.png"));
		addItem(item);
	}

	// Read files than
	list = m_rootdir.entryList(m_filter, QDir::Files | QDir::NoDotAndDotDot);
	for(i = 0; i < list.count(); i++) {
		ALyxListWidgetItem *item = new ALyxListWidgetItem(this, list[i]);
		item->setPixmap(QPixmap("./skins/default/icons/audio/audio-basic.png"));
		addItem(item);
	}
}
