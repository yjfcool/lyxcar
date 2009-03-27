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

#include "progressdlg.h"

ALyxProgressDialog::ALyxProgressDialog(QWidget *parent, ASkinner *s) :
	ALyxDialog(parent, s) {

	resize(290, 92);

	bar = new QProgressBar(this);
	bar->move(20, 40);
	bar->resize(250, 32);
	bar->setMaximum(100);
	bar->setMinimum(0);
}

void ALyxProgressDialog::setProgress(int percent) {
	bar->setValue(percent);
}
