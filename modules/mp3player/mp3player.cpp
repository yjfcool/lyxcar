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

mp3playerWindow::mp3playerWindow(QWidget *parent, ASkinner *s) {
	m_skinner = s;
	m_device = QString();

	setContentsMargins(0, 0, 0, 0);

	qDebug() << "mp3player is reading player settings";
	settings = new QSettings("./conf/mp3player.conf", QSettings::IniFormat, this);

	// Loading devices list
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

//	player = new MPlayerProcess(this);
//	connect(player, SIGNAL(readyReadStandardOutput()), this, SLOT(playerRead()));
//	connect(playBtn, SIGNAL(clicked()), this, SLOT(pauseCurrent()));

//	readCurrentMedia();
//	loadPlayList();

//	playCurrent();
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
	display = new ALyxDisplay(this);
	playBtn = new ALyxButton(this);
	firstBtn = new ALyxButton(this);
	backBtn = new ALyxButton(this);
	nextBtn = new ALyxButton(this);
	lastBtn = new ALyxButton(this);

	ALyxPushButton *selectDeviceBtn = new ALyxPushButton(this);
	selectDeviceBtn->setUpPixmap(QPixmap("./skins/default/mp3player/buttonbar_left_up.png"));
	selectDeviceBtn->setDownPixmap(QPixmap("./skins/default/mp3player/buttonbar_left_up.png"));
	selectDeviceBtn->setText("Device");
	selectDeviceBtn->setFont(QFont("Calibri", 12));
	selectDeviceBtn->move(60, 410);

	connect(selectDeviceBtn, SIGNAL(clicked()), this, SLOT(selectDevice()));

	ALyxPushButton *settingsBtn = new ALyxPushButton(this);
	settingsBtn->setUpPixmap(QPixmap("./skins/default/mp3player/buttonbar_mid_up.png"));
	settingsBtn->setDownPixmap(QPixmap("./skins/default/mp3player/buttonbar_mid_up.png"));
	settingsBtn->setText("Settings");
	settingsBtn->setFont(QFont("Calibri", 12));
	settingsBtn->move(176, 410);

	ALyxPushButton *testBtn = new ALyxPushButton(this);
	testBtn->setUpPixmap(QPixmap("./skins/default/mp3player/buttonbar_right_up.png"));
	testBtn->setDownPixmap(QPixmap("./skins/default/mp3player/buttonbar_right_up.png"));
	testBtn->setText("Test");
	testBtn->setFont(QFont("Calibri", 12));
	testBtn->move(292, 410);

	ALyxPushButton *repeatModeBtn = new ALyxPushButton(this);
	repeatModeBtn->setUpPixmap(QPixmap("./skins/default/mp3player/buttonbar_left_up.png"));
	repeatModeBtn->setDownPixmap(QPixmap("./skins/default/mp3player/buttonbar_left_up.png"));
	repeatModeBtn->setText("Repeat all");
	repeatModeBtn->setFont(QFont("Calibri", 12));
	repeatModeBtn->move(488, 410);
	ALyxPushButton *displayModeBtn = new ALyxPushButton(this);
	displayModeBtn->setUpPixmap(QPixmap("./skins/default/mp3player/buttonbar_right_up.png"));
	displayModeBtn->setDownPixmap(QPixmap("./skins/default/mp3player/buttonbar_right_up.png"));
	displayModeBtn->setText("Albums");
	displayModeBtn->setFont(QFont("Calibri", 12));
	displayModeBtn->move(604, 410);
	
	playList = new ALyxListWidget(this, m_skinner);
	playList->move(450, 10);
	playList->setFixedSize(330, 390);

	QDomElement displayElement = m_skinner->skinModuleElement("mp3player", "display");
	QString background = displayElement.attribute("background");
	QString fontfamily = displayElement.attribute("font-family");
	QString fontsize = displayElement.attribute("font-size");
	qDebug() << "mp3player display background" << background << "font-family" << fontfamily << "font-size" << fontsize;

	display->setObjectName("display");
	display->setBackgroundPixmap(QPixmap(m_skinner->skinModuleImagePath("mp3player")+background));

	QDomElement rectElement = displayElement.firstChildElement("rect");
	if(!rectElement.isNull()) {
		display->move(rectElement.attribute("x").toInt(), rectElement.attribute("y").toInt());
		display->setFixedSize(rectElement.attribute("width").toInt(), rectElement.attribute("height").toInt());
	} else {
	 	qDebug() << "Warning: no initial rectangle for" << display->objectName() << "defined";
	}

	playBtn->setSkin(m_skinner, "mp3player", "play");
	firstBtn->setSkin(m_skinner, "mp3player", "first");
	backBtn->setSkin(m_skinner, "mp3player", "back");
	lastBtn->setSkin(m_skinner, "mp3player", "last");
	nextBtn->setSkin(m_skinner, "mp3player", "next");
}

void mp3playerWindow::playerRead() {
	//testText->append(player->readAllStandardOutput());
}

//
// Scan current selected device for media files
// collect ID3 information and fill playlist.
//
void mp3playerWindow::loadDeviceContents() {
	QString device = m_device;
	qDebug() << "Loading device contents from" << device;

	QDirIterator it(device, QDirIterator::Subdirectories);

//
// For Russian windows users whose tags are in cp-1251
//
#ifdef Q_OS_WIN32
	QTextCodec *codec = QTextCodec::codecForName("Windows-1251");
#endif

	playList->clear();
	albums.clear();
	while (it.hasNext()) {
		QString fullFilePath = it.next().toLocal8Bit();
		if((it.fileInfo().suffix() == "mp3") ||
		(it.fileInfo().suffix() == "ogg") ||
		(it.fileInfo().suffix() == "flac")) {
			TagLib::FileRef f(fullFilePath.toAscii().constData());

			QString artist = TStringToQString(f.tag()->artist());
			QString album = TStringToQString(f.tag()->album());
			QString title= TStringToQString(f.tag()->title());

//
// For Russian windows users whose tags are in cp-1251
//
#ifdef Q_OS_WIN32
			artist = codec->toUnicode(artist.toAscii());
			album = codec->toUnicode(album.toAscii());
			title = codec->toUnicode(title.toAscii());
#endif
			albums[artist+"\n"+album].insert(title, fullFilePath);
		}
	} 

	// Fill the playlist with album entries
	foreach(QString albumName, albums.keys()) {
		qDebug() << albumName;
		ALyxListWidgetItem *item = new ALyxListWidgetItem(playList);
		item->setText(albumName);
		item->setPixmap(QPixmap("./skins/default/mp3player/cdplayer.png"));
		playList->addItem(item);
	}
}

void mp3playerWindow::readCurrentMedia() {
	/*QDirModel *model = new QDirModel;
	mediaTree->setModel(model);

	mediaTree->setRootIndex(model->index(QDir("/").absolutePath())); 
	((QHeaderView*)mediaTree->header())->hideSection(1);
	((QHeaderView*)mediaTree->header())->hideSection(2);
	((QHeaderView*)mediaTree->header())->hideSection(3);*/
}

void mp3playerWindow::playCurrent() {
	player->play();
}

void mp3playerWindow::stopCurrent() {
	player->write(QByteArray("stop\n"));
}

void mp3playerWindow::pauseCurrent() {
	player->write(QByteArray("pause\n"));
}

/*
 * Module activation procedure
 */
QWidget * mp3playerModule::activate(QWidget *parent) {
	moduleWindow = new mp3playerWindow(parent, m_skinner);

	return moduleWindow;
}
void mp3playerModule::deactivate(QString deactivateFor) {
    emit deactivated(deactivateFor);
}

QWidget * mp3playerModule::activateApplet(QWidget *parent) {
	return 0;
}

Q_EXPORT_PLUGIN2(mp3player, mp3playerModule);
