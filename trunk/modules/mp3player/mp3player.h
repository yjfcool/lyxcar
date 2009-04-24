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
#include <QTextCodec>

#include "m_interface.h"
#include "buttons.h"
#include "skinner.h"
#include "lists.h"
#include "scrolllabel.h"
#include "display.h"
#include "devicesdlg.h"
#include "playerdisplay.h"
#include "foldercontentsloader.h"
#include "progressdlg.h"
#include "database.h"

#include <phonon/mediasource.h>
#include <phonon/mediaobject.h>

#include <taglib.h>
#include <fileref.h>
#include <tag.h>
#include <id3v1tag.h>
#include <id3v2tag.h>
#include <tstring.h>



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

// File name - track name
typedef QHash<QString,QString> mp3playerAlbumContents;

class mp3playerWindow : public QWidget {
	Q_OBJECT
	public:
		mp3playerWindow(QWidget *parent = 0, ASkinner *s = 0, Phonon::AudioOutput *output = 0);
		~mp3playerWindow() { qDebug() << "mp3player window destroyed"; }

		QSettings *settings;
		
		void createWindow();
		void setSkinner(ASkinner *s) { m_skinner = s; }
		void setAudioOutput(Phonon::AudioOutput *output) { m_audioOutput = output; }

	public slots:
		void	playAlbum();
		void	playTrack();
		void	playCurrent();
		void	stopCurrent();
		void 	pauseCurrent();

		void	playerRead();

		void	loadDeviceContents();
		void	selectDevice();
		void	fillPlayList();
		void	displayAlbums();
	signals:

	private slots:
		void	deviceSelection(QString operation);
		void	fileFound(QString fileName);

	private:
		ASkinner *m_skinner;
		M_Interface *m_Interface;
		QTextCodec *tagCodec;

		QHash<QString, QString> m_devices; // Devices list from conf file
		QString	m_device; // Currently selected device

		AMp3PlayerDisplay *display;
		mp3playerDatabase *m_dbase;

		ALyxListWidget *playList;
		ALyxListWidget *trackList;

		ALyxButton *firstBtn;
		ALyxButton *backBtn;
		ALyxButton *playBtn;
		ALyxButton *nextBtn;
		ALyxButton *lastBtn;

		// Album name - tracks
		QHash<QString, mp3playerAlbumContents> albums;

		QString m_currentAlbumPlaying;
		QString m_currentTrackPlaying;
		QString m_currentFilePlaying;

		ALyxProgressDialog *progressDlg;

		Phonon::MediaObject *m_mediaObject;
		Phonon::AudioOutput *m_audioOutput;


		void	readCurrentMedia();
		void	loadAlbumTracks(QString album);
};

#endif
