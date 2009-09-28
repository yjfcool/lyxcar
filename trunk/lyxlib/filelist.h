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

#ifndef _FILELIST_H_
#define _FILELIST_H_

#include "lists.h"

class ALyxFileListWidget : public ALyxListWidget {
	Q_OBJECT
public:
	ALyxFileListWidget(QWidget *parent, ASkinner *skinner);

	QDir	dir() { return m_rootdir; }
	void	setRootDir(QDir dir) { m_rootdir = dir; refresh(); }
	void	setRootDir(QString dir) { m_rootdir = QDir(dir); refresh(); }
	void	setFilter(QStringList filter) { m_filter = filter; refresh(); }
	void	refresh();

private:
	QDir		m_rootdir;
	QStringList	m_filter;

	void	readRootDir();
	void	fileDoubleClicked(QString fileName);
	void	directoryDoubleClicked(QString dirName);

protected:
	void mouseDoubleClickEvent(QMouseEvent *e);

signals:
	void	fileActivated(QString fileName);
};

#endif // _FILELIST_H_
