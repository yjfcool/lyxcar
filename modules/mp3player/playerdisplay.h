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

#ifndef AMP3PLAYERDISPLAY_H
#define AMP3PLAYERDISPLAY_H

#include <QtXml>

#include "display.h"
#include "scrolllabel.h"
#include "skinner.h"

class AMp3PlayerDisplay : public QWidget
{
	Q_OBJECT
	public:
		AMp3PlayerDisplay(QWidget *parent = 0, ASkinner *skinner = 0);
		~AMp3PlayerDisplay();

		void setSongTitle(QString title);
		void setSongDuration(QString duration);

		void setPlaying(bool isPlaying);
		void setPaused(bool isPaused);
		void setRepeat(bool repeat);

	private:
		ALyxScrollLabel *songTitleLbl;
		QLabel	*songDurationLbl;

		QLabel	*playIcon;
		QLabel	*pausedIcon;
		QLabel	*repeatIcon;
};

#endif // AMP3PLAYERDISPLAY_H
