/*
 * Copyright (C) 2008-2009 Pavlov Denis
 *
 * Main home module.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or any later version.
 *
*/

#include "animated.h"

ALyxAnimation::ALyxAnimation(QObject *parent, ALyxControl *control) : QObject(parent) {
	m_control = control;

	timer = new QTimer();
	timer->setInterval(10);

	m_currentTime = 0;
	m_currentAnimationStop = 0;
	m_totalAnimationTime = 0;

	QObject::connect(timer, SIGNAL(timeout()), this, SLOT(animateStep()));
}

ALyxAnimation::~ALyxAnimation() {

}

void ALyxAnimation::start() {
	// Transform control
	ALyxAnimationStop stop = stops[0];
	m_control->move(stop.x(), stop.y());
	m_control->resize(stop.width(), stop.height());
	m_control->setOpacity(stop.opacity());

	timer->start();
}

void ALyxAnimation::animateStep() {
	// Get current animation stop
	ALyxAnimationStop c_stop = stops[m_currentAnimationStop];

	// Get next animation stop
	ALyxAnimationStop n_stop = stops[m_currentAnimationStop+1];

	// Calculate time difference between stops
	int time_diff = n_stop.time() - c_stop.time();
	if(m_currentTime == n_stop.time()) {
		m_currentAnimationStop++;
		qDebug() << "Current animation stop is" << m_currentAnimationStop;
	}

	// Calculate movement in one tick
	qreal x_diff = (n_stop.x() - c_stop.x()) / time_diff;
	qreal y_diff = (n_stop.y() - c_stop.y()) / time_diff;
	qreal w_diff = (n_stop.width() - c_stop.width()) / time_diff;
	qreal h_diff = (n_stop.height() - c_stop.height()) / time_diff;
	qreal opa_diff = (n_stop.opacity() - c_stop.opacity()) / time_diff;
	
	// Transform control
	m_control->move(m_control->x() + x_diff, m_control->y() + y_diff);
	m_control->resize(m_control->width() + w_diff, m_control->height() + h_diff);
	m_control->setOpacity(m_control->opacity() + opa_diff);

	m_currentTime++;
	if(m_currentTime > m_totalAnimationTime) {
		timer->stop();
		// Set last time stop animation step
		m_control->move(n_stop.x(), n_stop.y());
		m_control->resize(n_stop.width(), n_stop.height());
		m_control->setOpacity(n_stop.opacity());

		//
		m_currentTime = 0;
		qDebug() << "Animation stopped";
	}
}
