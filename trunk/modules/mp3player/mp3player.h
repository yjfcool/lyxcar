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

#ifndef __MP3PLAYER_H__
#define __MP3PLAYER_H__

#include <QWidget>
#include <QObject>
#include <QProcess>
#include <QSettings>

#include "mplayerprocess.h"

#include "m_interface.h"
#include "buttons.h"
#include "skinner.h"
#include "lists.h"
#include "scrolllabel.h"
#include "display.h"
#include "devicesdlg.h"


class mp3playerModule : public QObject, public M_Interface {
	Q_OBJECT
	Q_INTERFACES(M_Interface)

	public:
		QWidget * activate(QWidget *parent = 0);
		QWidget * activateApplet(QWidget *parent = 0);
		void deactivate(QString deactivateFor = "");

	signals:
		void demandActivation(QString moduleName);
		void deactivated(QString deactivateFor);
};

class mp3playerWindow : public QWidget {
	Q_OBJECT
	public:
		mp3playerWindow(QWidget *parent = 0, ASkinner *s = 0);
		~mp3playerWindow() { qDebug() << "mp3player window destroyed"; }

		MPlayerProcess *player;
		QSettings *settings;
		
		void createWindow();
		void setSkinner(ASkinner *s) { m_skinner = s; }

	public slots:
		void	playCurrent();
		void	stopCurrent();
		void 	pauseCurrent();

		void	playerRead();

		void	loadPlayList();
		void	selectDevice();

	private slots:
		void	deviceSelection(QString operation);

	private:
		ASkinner *m_skinner;
		M_Interface *m_Interface;

		QMap<QString, QString> m_devices; // Devices list from conf file

		ALyxButton *firstBtn;
		ALyxButton *backBtn;
		ALyxButton *playBtn;
		ALyxButton *nextBtn;
		ALyxButton *lastBtn;

		void	readCurrentMedia();
};

#endif