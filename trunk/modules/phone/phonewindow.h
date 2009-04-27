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

#ifndef __PHONEWINDOW_H__
#define __PHONEWINDOW_H__

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>

#include <phonon/audiooutput.h>

#include "lyxlib/skinner.h"
#include "lyxlib/lists.h"

class phoneWindow : public QWidget {
    Q_OBJECT
    public:
	phoneWindow(QWidget *parent = 0, ASkinner *skinner = 0, Phonon::AudioOutput *output = 0);
	~phoneWindow();

    private:
	QPushButton *phoneButtons[3][4];
};

#endif

