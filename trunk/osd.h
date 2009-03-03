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

#include <QWidget>

//! \brief This class implements on-screen-display for useful information, e.g. when changing volume or TV-channel.
class ALyxOSD : public QWidget {
	Q_OBJECT
	public:
		//! \brief Constructor, constructs OSD object.
		/*!
			\param parent specifies parent widget.
		*/
		ALyxOSD(QWidget *parent = 0);
		~ALyxOSD();
};