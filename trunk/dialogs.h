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

#include <QPainter>

#include "control.h"
#include "buttons.h"
#include "skinner.h"

class ALyxDialog : public ALyxControl {
	Q_OBJECT
	public:
		ALyxDialog(QWidget *parent = 0, ASkinner *s = 0);
		~ALyxDialog();

		void setTitle(QString title) { m_title = title; }
		QString title() { return m_title; }

		QList<ALyxButton *> buttons() { return m_buttons; }

		void addButton(ALyxButton *button) { m_buttons << qobject_cast<ALyxButton*>(button); } 

	private:
		QString m_title;
		QList<ALyxButton *> m_buttons;

	protected:
		void paintEvent(QPaintEvent *e);
		void resizeEvent(QResizeEvent *e);
};

#endif
