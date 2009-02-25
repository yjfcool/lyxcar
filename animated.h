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

#ifndef __ANIMATED_H__
#define __ANIMATED_H__

#include <QtGui>
#include <QWidget>
#include <QObject>

class ALyxAnimationStop {
	public:
		ALyxAnimationStop(int time, int x, int y, int w, int h, int accel = 0, int velo = 1) {
			m_time = time;
			m_w = w;
			m_h = h;
			m_x = x;
			m_y = y;
			m_accel = accel;
			m_velocity = velo;
		}
		~ALyxAnimationStop() {}

		int x() { return m_x; }
		int y() { return m_y; }
		int width() { return m_w; }
		int height() { return m_h; }
		int time() { return m_time; }
	private:
		int m_time;
		int m_w;
		int m_h;
		int m_x;
		int m_y;
		int m_accel;
		int m_velocity;
};

typedef QList<ALyxAnimationStop> ALyxAnimationStops;

//! \brief This class implements an animation of Lyx controls, such as buttons.
//!
//! Controls are animated through <ALyxAnimationStop> time stops.
//! There are two types of transformations of a control: moving and blending.
//! Every animation going between two time stops goes as a linear transformation
//! with a given velocity and coordinates. In other words, when the control transforms
//! it's size from 0,0 to 100,100 in 50ms, and the transformation is defined by 2 time stops
//! it changes regularly by 20 pixels in 1ms.
class ALyxAnimation : public QObject {
	Q_OBJECT
	public:
		ALyxAnimation(QObject * parent = 0, QWidget * control = 0);
		~ALyxAnimation();

		ALyxAnimationStops	stops;

		void start();
		void setAnimationTime(int ticks) { m_totalAnimationTime = ticks; }
	private:
		QWidget *m_control;

		int m_totalAnimationTime;

		int m_currentAnimationStop;
		int m_currentTime;

		QTimer *timer;

	public slots:
		void animateStep();
};

#endif
