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
#include "lists.h"
#include "skinner.h"
#include "animated.h"
#include "m_interface.h"

class playlistmgrModuleWidget : public QWidget {
	Q_OBJECT
	public:
		/* public members */
		playlistmgrModuleWidget(QWidget * parent = 0, ASkinner *s = 0);
		~playlistmgrModuleWidget();

		void setSkinner(ASkinner *s) { m_skinner = s; }
		
		void animateReverse();

	private:
		/* private members */
		ASkinner * m_skinner;
		
		ALyxAnimation *lastAnimation;

		// Buttons and animations in hashes with "button name" key.
		ALyxListWidget	*playList;
		ALyxListWidget	*folderList;

		// Add and remove buttons between lists
		ALyxButton	*addBtn;
		ALyxButton	*removeBtn;

		// Device selection buttons
		ALyxButton	*folderSelBtn;
		ALyxButton	*cdSelBtn;

		ALyxButton	*playBtn;	// When pressed it sends pause to mp3player and plays selected.
		ALyxButton	*stopBtn;	// When pressed it sends continue playing to mp3player.

		ALyxButton	*saveBtn;	// Playlist operations buttons
		ALyxButton	*loadBtn;

	private slots:
		void activateModule();
	
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
		void buttonClicked();
};

class playlistmgrModule : public QObject, M_Interface {
	Q_OBJECT
	Q_INTERFACES(M_Interface)

	public:
		QWidget * activate(QWidget * parent = 0);
		QWidget * activateApplet(QWidget * parent = 0);
		void deactivate(QString deactivateFor);

	private:
//		playlistmgrModuleApplet * appletWidget;
		playlistmgrModuleWidget * moduleWidget;
		
		QString nextModuleName;

	private slots:
		void deactivationFinished();

	signals:
		void demandActivation(QString moduleName);
		void deactivated(QString deactivateFor);

	public slots:
		//! \brief Module activation slot - creates and shows main module widget
		void activateMyself() {
			// Module emits signal demanding an activation.
			emit demandActivation(m_moduleName);
		}

		//! \brief Module activation slot - creates and shows main module <mname> widget
		void activateModuleWidget(QString mname) {
			// Module emits signal demanding an activation.
			emit demandActivation(mname);
		}
};

#endif
