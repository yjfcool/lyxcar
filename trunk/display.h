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

#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include "control.h"

//! \brief ALyxDisplay implements display widget which can contain
//! labels, icons, animations etc.
class ALyxDisplay : public ALyxControl {
	Q_OBJECT
	public:
		ALyxDisplay(QWidget *parent = 0);
		~ALyxDisplay();
	private:

	private slots:

	public slots:
};

#endif
