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

#ifndef ALYXGAUGE_H
#define ALYXGAUGE_H

#include "control.h"
#include "skinner.h"

class ALyxGauge : public ALyxControl {
	Q_OBJECT
	public:
		ALyxGauge(QWidget *parent = 0, ASkinner *s = 0);
		~ALyxGauge();

		void setScale(int min = 0, int max = 100, int begin_deg = 90, int end_deg = 270);

	private:
		int m_minPosition;
		int m_maxPosition;
		int m_position;

		int m_beginDegree;
		int m_endDegree;

		QPixmap *bolt;

		void paintEvent(QPaintEvent *e);

	public slots:
};

#endif // ALYXGAUGE_H
