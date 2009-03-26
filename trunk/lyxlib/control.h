/*
 * Copyright (C) 2008-2009 Pavlov Denis
 *
 * Control prototype.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or any later version.
 *
*/

#ifndef __LYXCONTROL_H__
#define __LYXCONTROL_H__

#include <QWidget>
#include <QDebug>

#include "skinner.h"

class ALyxControl : public QWidget {
	Q_OBJECT
	public:
		ALyxControl(QWidget *parent = 0, ASkinner *skinner = 0);
		~ALyxControl();

		void setOpacity(qreal opacity) { m_opacity = opacity; repaint(); }
		qreal opacity() { return m_opacity; }

		void setFixedSize(int w, int h);
		void setFixedSize(QSize s);

	protected:
		ASkinner *m_skinner;

		qreal m_opacity;
};

#endif
