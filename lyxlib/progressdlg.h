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

#ifndef PROGRESSDLG_H
#define PROGRESSDLG_H

#include <QWidget>
#include <QProgressBar>

#include "dialogs.h"

class ALyxProgressDialog : public ALyxDialog {
	Q_OBJECT
	public:
		ALyxProgressDialog(QWidget *parent = 0, ASkinner *s = 0);
		~ALyxProgressDialog() {}

		void setProgress(int percent);

	private:
		QProgressBar *bar;
};

#endif // PROGRESSDLG_H
