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

#ifndef __DIALOGS_H__
#define __DIALOGS_H__

#include "control.h"
#include "buttons.h"

class ALyxDialog : public ALyxControl {
    Q_OBJECT
    public:
	ALyxDialog(QWidget *parent = 0);
	~ALyxDialog();

	void setTitle(QString title) { m_title = title; }
	QString title() { return m_title; }

    private:
	QString m_title;

	void paintEvent(QPaintEvent *e);
};

#endif
