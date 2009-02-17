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

#ifndef __MP3PLAYER_H__
#define __MP3PLAYER_H__

#include <QWidget>
#include <QObject>
#include <QProcess>
#include <QSettings>

#include "ui_main.h"
#include "../../m_interface.h"
#include "mplayerprocess.h"

class mp3playerModule : public QObject, M_Interface {
	Q_OBJECT
	Q_INTERFACES(M_Interface)

	public:
		QWidget * activate(QWidget *parent = 0);
		QWidget * activateApplet(QWidget *parent = 0);
};

class mp3playerWindow : public QWidget, private Ui_mp3player {
	Q_OBJECT
	public:
		mp3playerWindow(QWidget *parent = 0);

		MPlayerProcess *player;

		QSettings *settings;

	public slots:
		void	playCurrent();
		void	stopCurrent();
		void 	pauseCurrent();

		void	playerRead();

		void	loadPlayList();

	private:
		M_Interface *mInterface;
		QLabel *label;

		void	readCurrentMedia();	
};

#endif
