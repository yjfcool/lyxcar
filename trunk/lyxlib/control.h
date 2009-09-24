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

class ALyxControlPrivate;

class ALyxControl : public QWidget {
	Q_OBJECT
	Q_DECLARE_PRIVATE(ALyxControl)
	public:
		ALyxControl(QWidget *parent = 0);
		~ALyxControl();

		//! \brief Sets control opacity from 0.0 to 1.0.
		void setOpacity(qreal opacity) { m_opacity = opacity; repaint(); }
		qreal opacity() const;

		//! \brief Sets control fixed size defined by width and height or QSize.
		void setFixedSize(int w, int h);
		void setFixedSize(QSize s);

		//! \brief Set ASkinner object to use for this instance of button.
		void setSkinner(ASkinner *s);

	protected:
		qreal		m_opacity;
		ASkinner	*m_skinner;
};

#endif
