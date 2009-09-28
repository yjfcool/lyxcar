/*
 * Copyright (C) 2008 Pavlov Denis
 *
 * Playlist manager module.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or any later version.
 *
*/

#ifndef __PLAYLISTMGR_H__
#define __PLAYLISTMGR_H__

#include <QtGui>
#include <QtXml>
#include <QPushButton>

#include "panel.h"
#include "buttons.h"
#include "filelist.h"
#include "skinner.h"
#include "animated.h"
#include "m_interface.h"

#include "../mp3player/playlist.h"

class playlistmgrModuleWidget : public QWidget {
	Q_OBJECT
	public:
		/* public members */
		playlistmgrModuleWidget(QWidget * parent = 0, ASkinner *s = 0);
		~playlistmgrModuleWidget();

		void setSkinner(ASkinner *s) { m_skinner = s; }
		void animateReverse();

		void fillPlayList();

		APlaylist *playListXML;

	private:
		/* private members */
		ASkinner * m_skinner;
		
		ALyxAnimation *lastAnimation;

		// Buttons and animations in hashes with "button name" key.
		ALyxListWidget		*playList;
		ALyxFileListWidget	*fileList;

		// Add and remove buttons between lists
		ALyxButton	*addBtn;
		ALyxButton	*removeBtn;

		// Device selection buttons
		ALyxButton	*folderSelBtn;
		ALyxButton	*cdSelBtn;

		ALyxPushButton	*playBtn;	// When pressed it sends pause to mp3player and plays selected.
		ALyxPushButton	*returnBtn;	// When pressed it sends continue playing to mp3player.

		ALyxPushButton	*saveBtn;	// Playlist operations buttons
		ALyxPushButton	*loadBtn;

	private slots:
	
	signals:
		void activateClicked(QString);
		void animationFinished();
};

class playlistmgrModuleApplet : public QWidget {
	Q_OBJECT
	public:
		/* public members */
		playlistmgrModuleApplet(QWidget * parent = 0, ASkinner *s = 0);
		~playlistmgrModuleApplet();

		void setSkinner(ASkinner *s) { m_skinner = s; }

	private:
		/* private members */
		ASkinner * m_skinner;

	private slots:

	signals:
};

class playlistmgrModule : public QObject, M_Interface {
	Q_OBJECT
	Q_INTERFACES(M_Interface)

	public:
		QWidget * activate(QWidget * parent = 0);
		QWidget * activateApplet(QWidget * parent = 0);
		void deactivate(QString deactivateFor);

	private:
		playlistmgrModuleWidget *m_moduleWidget;
		QString			m_nextModuleName;
		
	private slots:
		void deactivationFinished();

	signals:
		void demandActivation(QString moduleName);
		void deactivated(QString deactivateFor);

	public slots:
};

#endif
