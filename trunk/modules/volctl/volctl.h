/*
 * Copyright (C) 2008 Pavlov Denis
 *
 * Volume control module.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or any later version.
 *
*/

#ifndef __VOLCTL_H__
#define __VOLCTL_H__

#include <QtGui>
#include <QPushButton>

#include "panel.h"
#include "buttons.h"
#include "skinner.h"
#include "m_interface.h"

#include <phonon/audiooutput.h>

class volCtlModuleApplet : public QWidget {
	Q_OBJECT
	public:
		/* public members */		
		volCtlModuleApplet(QWidget * parent = 0, ASkinner *s = 0);
		~volCtlModuleApplet();

		void setSkinner(ASkinner *s) { m_skinner = s; }
		void setAudioOutput(Phonon::AudioOutput *output) { m_audioOutput = output; }
		void setOSD(ALyxOSD *osd) { m_osd = osd; }

	private:
		/* private members */
		ALyxButton * vol_up_button;
		ALyxButton * vol_down_button;
		ALyxButton * vol_mute_button;

		ASkinner * m_skinner;
		Phonon::AudioOutput *m_audioOutput;
		ALyxOSD	 * m_osd;
		
		QTimer *volumeChangeTimer;
		int	volumeChange;
		int	volume;

	private slots:
		void	volume_up();
		void	volume_down();
		void	volume_mute();
		void	volume_change();
};

class volCtlModule : public QObject, M_Interface {
	Q_OBJECT
	Q_INTERFACES(M_Interface)

	public:
		QWidget * activate(QWidget * parent = 0);
		QWidget * activateApplet(QWidget * parent = 0);
		void deactivate(QString deactivateFor) {}

	private:
		volCtlModuleApplet * appletWidget;
		
	signals:
		void demandActivation(QString);
};


#endif
