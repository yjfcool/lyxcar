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

#include <QtGui>
#include <QBoxLayout>
#include <QDirModel>

#include "mp3player.h"

mp3playerWindow::mp3playerWindow(QWidget *parent, ASkinner *s, Phonon::AudioOutput *output) {
	m_skinner = s;
	m_device = QString();
	setAudioOutput(output);

	m_dbase = new mp3playerDatabase(this); // Create connection to mp3s database

	m_mediaObject = new Phonon::MediaObject(this);	// Create new media object for this instance of player
	Phonon::Path path = Phonon::createPath(m_mediaObject, m_audioOutput);	// Connect it to audio output

	playTimer = new QTimer();
	playTimer->setInterval(500);
	connect(playTimer, SIGNAL(timeout()), this, SLOT(playTimerTimeout()));
  
	setContentsMargins(0, 0, 0, 0);

	qDebug() << "mp3player is reading player settings";
	settings = new QSettings("./conf/mp3player.conf", QSettings::IniFormat, this);

	// Loading media devices list
	settings->beginGroup("Devices");
	QStringList devs = settings->childKeys();
	// Parse [Devices]
	foreach(QString dev, devs) {
		m_devices[dev] = settings->value(dev).toString();
		QStringList dev_params = m_devices[dev].split("#");
		// Get active device sign
		if(dev_params.count() > 2) {
			if(dev_params[2] == "1") {
				m_device = dev_params[0];
			}
		}
	}

	createWindow();

	// If there is no device selected,
	// go to device selection dialog!
	if(m_device != "") {
		loadDeviceContents();
	} else {
		selectDevice();
	}
}

// SLOT
void mp3playerWindow::selectDevice() {

	// Create dialog
	ALyxDevicesDialog *dialog = new ALyxDevicesDialog(this, m_skinner);
	dialog->setWindowTitle(tr("Device selection"));
	dialog->move(200, 150);
	dialog->setFixedSize(400, 250);

	// Parse m_devices (list from config)
	foreach(QString dev, m_devices.keys()) {
		qDebug() << "Device in config" << dev;
		QStringList dev_params = m_devices[dev].split("#");
		QString point;
		QString icon;
		if(dev_params.count() > 0) {
			point = dev_params[0];
			if(dev_params.count() > 1) {
				icon = dev_params[1]; // Device icon
			} else {
			 	icon = "folder.png"; // Default icon
			}
			// Adding device to dialog's jogdial
			dialog->addDevice(point, dev, QString("./skins/default/mp3player/icons/")+icon);
			qDebug() << "Added to dialog" << point << dev;
			// Detecting active device
			if(dev_params.count() > 2) {
				if(dev_params[2] == "1" && m_device == "") { m_device = dev_params[0]; }
			}
		}
	}

	// Setting current active device by device PATH!
	if(m_device != "") {
		qDebug() << "Setting active device by path" << m_device;
		dialog->setActiveDeviceByPath(m_device);
	}

	dialog->show();

	// Connecting button actions to deviceSelection(QString operation)
	// There are two operations - "ok" and "cancel".
	// Te operation is passed to slot and will be processed there.
	connect(dialog, SIGNAL(buttonClicked(QString)), this, SLOT(deviceSelection(QString)));
}


// SLOT
// Processes device selection from ALyxDevicesDialog.
// If the operation is "ok", which means the "OK" button clicked,
// it changes active device and reloads a playlist.
// Any operation hides dialog and sets it's modality to false.
void mp3playerWindow::deviceSelection(QString operation) {
	qDebug() << "Active device is:" << qobject_cast<ALyxDevicesDialog *>(sender())->activeDevicePath();
	if((operation == "ok") &&
	   (qobject_cast<ALyxDevicesDialog *>(sender())->activeDevicePath() != m_device)) {
		m_device = qobject_cast<ALyxDevicesDialog *>(sender())->activeDevicePath();
		qDebug() << "Device selected:" << m_device;
		loadDeviceContents();
	}
	qobject_cast<ALyxDevicesDialog *>(sender())->setModal(false);
	qobject_cast<ALyxDevicesDialog *>(sender())->hide();

	delete sender();
}

void mp3playerWindow::createWindow() {
	playBtn = new ALyxButton(this);

	connect(playBtn, SIGNAL(clicked()), this, SLOT(playCurrent()));

	prevAlbumBtn = new ALyxButton(this);
	connect(prevAlbumBtn, SIGNAL(clicked()), this, SLOT(playPreviousAlbum()));

	prevBtn = new ALyxButton(this);
	connect(prevBtn, SIGNAL(clicked()), this, SLOT(playPrevious()));

	nextBtn = new ALyxButton(this);
	connect(nextBtn, SIGNAL(clicked()), this, SLOT(playNext()));

	nextAlbumBtn = new ALyxButton(this);
	connect(nextAlbumBtn, SIGNAL(clicked()), this, SLOT(playNextAlbum()));

	ALyxPushButton *selectDeviceBtn = new ALyxPushButton(this);
	selectDeviceBtn->setSkin(m_skinner, "mp3player", "device");
	selectDeviceBtn->setText("Device");
	selectDeviceBtn->setFont(QFont("Calibri", 12));

	connect(selectDeviceBtn, SIGNAL(clicked()), this, SLOT(selectDevice()));

	ALyxPushButton *settingsBtn = new ALyxPushButton(this);
	settingsBtn->setSkin(m_skinner, "mp3player", "settings");
	settingsBtn->setText("Settings");
	settingsBtn->setFont(QFont("Calibri", 12));

	ALyxPushButton *testBtn = new ALyxPushButton(this);
	testBtn->setSkin(m_skinner, "mp3player", "test");
	testBtn->setText("Test");
	testBtn->setFont(QFont("Calibri", 12));

	playlistEditBtn = new ALyxPushButton(this);
	playlistEditBtn->setSkin(m_skinner, "mp3player", "playlist");
	playlistEditBtn->setText("Playlist");
        playlistEditBtn->setFont(QFont("Calibri", 12));
	connect(playlistEditBtn, SIGNAL(clicked()), this, SLOT(activatePlaylistEditor()));

        ALyxPushButton *displayModeBtn = new ALyxPushButton(this);
	displayModeBtn->setSkin(m_skinner, "mp3player", "display");
	displayModeBtn->setText("Albums");
	displayModeBtn->setFont(QFont("Calibri", 12));
	connect(displayModeBtn, SIGNAL(clicked()), this, SLOT(displayAlbums()));
	
	playList = new ALyxListWidget(this, m_skinner);
	playList->setSkin(NULL, "mp3player", "playlist");
	connect(playList, SIGNAL(doubleClicked()), this, SLOT(playAlbum()));

	trackList = new ALyxListWidget(this, m_skinner);
	trackList->setSkin(NULL, "mp3player", "playlist");
	trackList->setVisible(false); // Hide it by default until the album is selected
	connect(trackList, SIGNAL(doubleClicked()), this, SLOT(playTrack()));

	playBtn->setSkin(m_skinner, "mp3player", "play");
	prevAlbumBtn->setSkin(m_skinner, "mp3player", "first");
	prevBtn->setSkin(m_skinner, "mp3player", "back");
	nextAlbumBtn->setSkin(m_skinner, "mp3player", "last");
	nextBtn->setSkin(m_skinner, "mp3player", "next");

	display = new AMp3PlayerDisplay(this, m_skinner);
}

void mp3playerWindow::playerRead() {}

//
// Scan current selected device for media files
// collect ID3 information and fill playlist.
//
void mp3playerWindow::loadDeviceContents() {
	QString device = m_device;
	qDebug() << "Loading device contents from" << device;

	playList->clear();
	trackList->clear();
	albums.clear();

	progressDlg = new ALyxProgressDialog(this);
	progressDlg->setWindowTitle(tr("Progress"));
	progressDlg->setProgress(50);
	progressDlg->center();

	progressDlg->show();

//
// For Russian windows users whose tags are in cp-1251
//
#ifdef Q_OS_WIN32
	tagCodec = QTextCodec::codecForName("Windows-1251");
#endif

	FolderContentsLoader *loader = new FolderContentsLoader();
	loader->setFolder(device);

	connect(loader, SIGNAL(finished()), this, SLOT(fillPlayList()));
	connect(loader, SIGNAL(fileFound(QString)), this, SLOT(fileFound(QString)));

	loader->start();
}

// Media loader thread calls this when media file is found
void mp3playerWindow::fileFound(QString fileName) {
			qDebug() << "Found file" << fileName;

			QString artist;
			QString album;
			QString title;

			if(m_dbase->ifExists(fileName)) {
			    ATrackData td;
			    td = m_dbase->getTrack(fileName);

			    artist = td.artist;
			    album = td.album;
			    title = td.trackName;
			} else {
			    QString t_fileName = fileName.toLocal8Bit();
			    TagLib::FileRef f(t_fileName.toAscii().constData());

			    artist = TStringToQString(f.tag()->artist());
			    album = TStringToQString(f.tag()->album());
			    title = TStringToQString(f.tag()->title());

// For Russian windows users whose tags are in cp-1251
#ifdef Q_OS_WIN32
			    artist = tagCodec->toUnicode(artist.toAscii());
			    album = tagCodec->toUnicode(album.toAscii());
			    title = tagCodec->toUnicode(title.toAscii());
#endif
			    m_dbase->addTrack(fileName, artist, album, title, "00:00");
			}
			// Insert into albums database structure containing
			// song title as a key and it's file name as a value (QHash)
			albums[artist+"\n"+album].insert(title, fileName);
}

// Media loader thread calls this when it is finished
void mp3playerWindow::fillPlayList() {
	qDebug() << "Media loader is filling the play list";

	disconnect(sender(), SIGNAL(fileFound(QString)), this, SLOT(fileFound(QString)));
	disconnect(sender(), SIGNAL(finished()), this, SLOT(fillPlayList()));

	// Fill the playlist with album entries
	foreach(QString albumName, albums.keys()) {
		qDebug() << albumName;
		ALyxListWidgetItem *item = new ALyxListWidgetItem(playList);
		item->setText(albumName);
		item->setPixmap(QPixmap("./skins/default/icons/cdplayer.png"));
		playList->addItem(item);
	}

	progressDlg->setModal(false);
	progressDlg->hide();

	delete progressDlg;
}

void mp3playerWindow::loadAlbumTracks(QString album) {
	qDebug() << "Loading tracks of" << album << "album to tracklist";
	trackList->clear();

	QStringList tracks = albums[album].keys();
	foreach(QString trackName, tracks) {
		ALyxListWidgetItem *item = new ALyxListWidgetItem(trackList);
		item->setText(trackName);
		item->setPixmap(QPixmap("./skins/default/icons/audio/audio-x-wav.png"));
		trackList->addItem(item);
	}
}

void mp3playerWindow::displayAlbums() {
    trackList->hide();
    playList->show();
}

// SLOT executed every 500ms to update song remaining time and so on.
void mp3playerWindow::playTimerTimeout() {
    QTime t_time = QTime(0, 0, 0);
    QTime m_time = t_time.addMSecs(m_mediaObject->remainingTime());

    QString t_str = m_time.toString("mm:ss");
    display->setSongDuration(t_str);

//    qDebug() << "Time is:" << m_mediaObject->remainingTime();
}

void mp3playerWindow::playCurrent() {
	qDebug() << "Mp3Player STARTS playing current:\n"
	    << "album:" << m_currentAlbumPlaying
	    << "\ntrack:" << m_currentTrackPlaying
	    << "\nfile:" << m_currentFilePlaying;

	playBtn->setSkin(m_skinner, "mp3player", "stop");

	disconnect(playBtn, SIGNAL(clicked()), this, SLOT(playCurrent()));
	connect(playBtn, SIGNAL(clicked()), this, SLOT(stopCurrent()));

	display->setPlaying(true);
	QString tmp = m_currentAlbumPlaying;
	display->setSongTitle(tmp.replace("\n", " - ")+" *** ");

	playTimer->stop();
	m_mediaObject->stop();
	m_mediaObject->setCurrentSource(Phonon::MediaSource(m_currentFilePlaying));
	m_mediaObject->play();
	playTimer->start();
	
	//
	// Select currently playing track in list
	//
	
}

/*
 * Begins playing selected track.
 * Sets currentTrack to selected and calls playCurrent().
 */
void mp3playerWindow::playTrack() {
    if(trackList->selectedIndex() >= 0) {
        ALyxListWidgetItem *item = trackList->selectedItem();
        m_currentTrackPlaying = item->text();
	qDebug() << m_currentAlbumPlaying;
        m_currentFilePlaying = albums[m_currentAlbumPlaying].value(m_currentTrackPlaying);

	playCurrent();
    }
}

/*
 * Begins playing selected album.
 * Sets currentAlbumPlaying, loads album tracks into list and sets currentTrack
 * to the first one. Than calls playCurrent().
 */
void mp3playerWindow::playAlbum() {
	if(playList->selectedIndex() >= 0) {
		ALyxListWidgetItem *item = playList->selectedItem();

		// Get album name from the list
		if(item->text() != m_currentAlbumPlaying) {
		    m_currentAlbumPlaying = item->text();
		    m_currentTrackPlaying = "";
		    m_currentFilePlaying = "";
		}

		// Load tracks to current playing album
		loadAlbumTracks(m_currentAlbumPlaying);

		// If there is no track or file defined play the first one in album
		if((m_currentTrackPlaying == "") || (m_currentFilePlaying == "")) {
		    if(trackList->size() > 0) {	// If the album has tracks start with the first one
		        m_currentTrackPlaying = albums[item->text()].keys().value(0);
			m_currentFilePlaying = albums[item->text()].values().value(0);
			trackList->selectItem(0);
		    } else {
			// Album has no tracks
		    }
		}

		playList->hide();
		trackList->show();
		
		// Start playing current selected album
		playCurrent();
	} else {
		qDebug() << "Mp3Player has nothing to play, nothing is selected";
	}
}

void mp3playerWindow::stopCurrent() {
	qDebug() << "Mp3Player STOPS playing";
	playBtn->setSkin(m_skinner, "mp3player", "play");
	display->setPlaying(false);
	display->setPaused(false);

	m_mediaObject->stop();

	connect(playBtn, SIGNAL(clicked()), this, SLOT(playCurrent()));
	disconnect(playBtn, SIGNAL(clicked()), this, SLOT(stopCurrent()));
}

void mp3playerWindow::playNextAlbum() {
    // If there is albums to play select next one
    QStringList m_albums = albums.keys();
    int m_currentAlbumIndex = m_albums.indexOf(m_currentAlbumPlaying);

    if(m_albums.size()-m_currentAlbumIndex > 1) {
	m_currentAlbumPlaying = m_albums[m_currentAlbumIndex+1];	// Next album
	if(albums[m_currentAlbumPlaying].keys().size() > 0) {
	    m_currentTrackPlaying = albums[m_currentAlbumPlaying].keys().value(0);
	    m_currentFilePlaying = albums[m_currentAlbumPlaying].values().value(0);

	    // Load tracks to current playing album
	    loadAlbumTracks(m_currentAlbumPlaying);
            playCurrent();

	    // Make track selection
	    playList->selectItem(m_currentAlbumIndex+1);
	    trackList->selectItem(0);
	} else {
	    qDebug() << "mp3player: Album has no tracks! That's an error!\nGoing to next track.";
	    playNextAlbum();
	}
    } else {
		// Disable next button
    }
}

void mp3playerWindow::playNext() {
    if((m_currentTrackPlaying != "") && (m_currentFilePlaying != "")) {
        QStringList m_albums = albums.keys();
	QStringList m_tracks = albums[m_currentAlbumPlaying].keys();

        int m_currentTrackIndex = m_tracks.indexOf(m_currentTrackPlaying);
	int m_currentAlbumIndex = m_albums.indexOf(m_currentAlbumPlaying);

	// Next track
	if(m_tracks.size()-m_currentTrackIndex > 1) {
	    m_currentTrackPlaying = m_tracks[m_currentTrackIndex+1];
	    m_currentFilePlaying = albums[m_currentAlbumPlaying].value(m_currentTrackPlaying);
	    playCurrent();

	    playList->selectItem(m_currentAlbumIndex);
	    trackList->selectItem(m_currentTrackIndex+1);
	} else {
	    playNextAlbum();
	}
    }
}

void mp3playerWindow::playPrevious() {
    if((m_currentTrackPlaying != "") && (m_currentFilePlaying != "")) {
        QStringList m_albums = albums.keys();
	QStringList m_tracks = albums[m_currentAlbumPlaying].keys();

        int m_currentTrackIndex = m_tracks.indexOf(m_currentTrackPlaying);
	int m_currentAlbumIndex = m_albums.indexOf(m_currentAlbumPlaying);

	// Previous track
	if(m_currentTrackIndex > 0) {
	    m_currentTrackPlaying = m_tracks[m_currentTrackIndex-1];
	    m_currentFilePlaying = albums[m_currentAlbumPlaying].value(m_currentTrackPlaying);
	    playCurrent();

	    playList->selectItem(m_currentAlbumIndex);
	    trackList->selectItem(m_currentTrackIndex-1);
	} else {
	    playPreviousAlbum();
	}
    }
}

void mp3playerWindow::playPreviousAlbum() {
    // If there is albums to play select next one
    QStringList m_albums = albums.keys();
    int m_currentAlbumIndex = m_albums.indexOf(m_currentAlbumPlaying);

    if(m_currentAlbumIndex > 0) {
	m_currentAlbumPlaying = m_albums[m_currentAlbumIndex-1];	// Prev album
	if(albums[m_currentAlbumPlaying].keys().size() > 0) {
	    m_currentTrackPlaying = albums[m_currentAlbumPlaying].keys().value(albums[m_currentAlbumPlaying].keys().size()-1);
	    m_currentFilePlaying = albums[m_currentAlbumPlaying].values().value(albums[m_currentAlbumPlaying].values().size()-1);

	    // Load tracks to current playing album
	    loadAlbumTracks(m_currentAlbumPlaying);
            playCurrent();

	    // Make track selection
	    playList->selectItem(m_currentAlbumIndex-1);
	    trackList->selectItem(albums[m_currentAlbumPlaying].keys().size()-1);
	} else {
	    qDebug() << "mp3player: Album has no tracks! That's an error!\nGoing to next track.";
	    playPreviousAlbum();
	}
    } else {
		// Disable previous button
    }
}

void mp3playerWindow::pauseCurrent() {
	qDebug() << "Mp3Player PAUSES playing";
	display->setPaused(true);
	m_mediaObject->pause();
}

/*
 * Module activation procedure
 */
QWidget * mp3playerModule::activate(QWidget *parent) {
	if(!moduleWindow) {
		moduleWindow = new mp3playerWindow(parent, m_skinner, m_audioOutput);
		setClosable(false);

		connect(qobject_cast<mp3playerWindow*>(moduleWindow)->playlistEditBtn, SIGNAL(clicked()), this, SLOT(activatePlaylistEditor()));
	} else {
		moduleWindow->show();
	}

	return moduleWindow;
}

void  mp3playerModule::activatePlaylistEditor() {
	qDebug() << "mp3player caller playlist manager";
	emit demandActivation("playlistmgr");
}

void mp3playerModule::deactivate(QString deactivateFor) {
    emit deactivated(deactivateFor);
}

QWidget * mp3playerModule::activateApplet(QWidget *parent) {
	return 0;
}

Q_EXPORT_PLUGIN2(mp3player, mp3playerModule);
