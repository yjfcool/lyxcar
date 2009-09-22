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
#include "skinner.h"
#include "animated.h"
#include "m_interface.h"

class playListMgrModuleWidget : public QWidget {
	Q_OBJECT
	public:
		/* public members */
		playListMgrModuleWidget(QWidget * parent = 0, ASkinner *s = 0);
		~playListMgrModuleWidget();

		void setSkinner(ASkinner *s) { m_skinner = s; }
		
		void animateReverse();

	private:
		/* private members */
		ASkinner * m_skinner;
		
		ALyxAnimation *lastAnimation;

		// Buttons and animations in hashes with "button name" key.
		QHash<QString, ALyxAnimation *> animations;
		QHash<QString, ALyxButton *> buttons;

	private slots:
		void activateModule();
	
	signals:
		void activateClicked(QString);
		void animationFinished();
};

class playListMgrModuleApplet : public QWidget {
	Q_OBJECT
	public:
		/* public members */
		playListMgrModuleApplet(QWidget * parent = 0, ASkinner *s = 0);
		~playListMgrModuleApplet();

		void setSkinner(ASkinner *s) { m_skinner = s; }

	private:
		/* private members */
		ASkinner * m_skinner;

	private slots:


	signals:
		void buttonClicked();
};

class playListMgrModule : public QObject, M_Interface {
	Q_OBJECT
	Q_INTERFACES(M_Interface)

	public:
		QWidget * activate(QWidget * parent = 0);
		QWidget * activateApplet(QWidget * parent = 0);
		void deactivate(QString deactivateFor);

	private:
		playListMgrModuleApplet * appletWidget;
		playListMgrModuleWidget * moduleWidget;
		
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
