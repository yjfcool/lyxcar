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

#include "gauges.h"

#include <math.h>

ALyxGauge::ALyxGauge(QWidget *parent, ASkinner *s) {
	m_minPosition = 1;
	m_maxPosition = 100;
	m_position = 20;

	m_beginDegree = 45;
	m_endDegree = 270;

	bolt = new QPixmap("./skins/default/bolt_small.png");
}

ALyxGauge::~ALyxGauge() {

}

void ALyxGauge::setScale(int min, int max, int begin_deg, int end_deg) {
	m_minPosition = min;
	m_maxPosition = max;
	m_beginDegree = begin_deg;
	m_endDegree = end_deg;
	repaint();
}

void ALyxGauge::paintEvent(QPaintEvent *e) {
	QPainter p(this);
	QSize s = size();
	QPoint center(s.width() / 2, s.height() / 2);
	QColor boltColor(255, 0, 0);
	QColor ticksColor(0, 0, 255);
	int radius = 120;
	int boltLength = 100;
	int signTickPosition = 5;
	int ticksDensity = 2;

	qreal oneStepDegrees = (m_endDegree - m_beginDegree) / (m_maxPosition - m_minPosition);

	p.setRenderHint(QPainter::Antialiasing, true);

	// Draw ticks
	p.setPen(ticksColor);
	int tc = 0;
	for(int a = m_minPosition; a <= m_maxPosition; a+=ticksDensity) {
		qreal a_rad = 3.1415926 / 180.0 * a * oneStepDegrees + m_beginDegree;
//		float tickX = center.x() + sin(a_rad);
//		float tickY = center.y() + cos(a_rad);
		int tickLength = 0;
		if((tc % signTickPosition) == 0) {
			tickLength = 10;
		} else {
			tickLength = 6;
		}
		QPointF tickBegin(center.x() - sin(a_rad) * (radius - tickLength),
				  center.y() + cos(a_rad) * (radius - tickLength));
		QPointF tickEnd(center.x() - sin(a_rad) * radius,
				center.y() + cos(a_rad) * radius);

		p.drawLine(tickBegin, tickEnd);
		tc++;
	}

	// Draw bolt

	QTransform boltTransform;
	QPoint boltCenterOffset(112, bolt->height() / 2);
	boltTransform.rotate(oneStepDegrees * m_position + m_beginDegree);
	p.translate(center-boltCenterOffset);
	p.drawPixmap(0, 0, *bolt);
	p.translate(-(center-boltCenterOffset));

	qreal bolt_rad = 3.1415926 / 180 * (oneStepDegrees * m_position + m_beginDegree);
	QPointF boltEnd(center.x() - sin(bolt_rad) * boltLength,
			center.y() + cos(bolt_rad) * boltLength);
	p.setPen(boltColor);
	p.drawLine(center, boltEnd);

	p.end();
}
