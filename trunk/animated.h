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

#include "control.h"

//! \brief This is an animation stop point for ALyxAnimation object.
//! It defines the state of a control (position, size and opacity) at time defined by <time>.
//!
//! It may also be defined an acceleration in percent that means that the last step state change of animation queue
//! will be faster or slower than the first. Of course the acceleration is divided by number of steps in that queue.
//!
//! For example:
//!  - first step is ALyxAnimationStop(0, 0, 0, 0, 0, 1.5)
//!  - second step is ALyxAnimationStop(30, 0, 0, 100, 100)
//! According to this the animation goes in 30 ticks and accelerates by 50% from 1st step to 2nd one.
class ALyxAnimationStop {
	public:
		ALyxAnimationStop(int time, int x, int y, int w, int h, qreal opacity = 1.0, qreal accel = 1.0, int velo = 1) {
			m_time = time;
			m_w = w;
			m_h = h;
			m_x = x;
			m_y = y;
			m_accel = accel;
			m_velocity = velo;
			m_opacity = opacity;
		}
		~ALyxAnimationStop() {}

		int x() { return m_x; }
		int y() { return m_y; }
		int width() { return m_w; }
		int height() { return m_h; }
		int time() { return m_time; }
		qreal opacity() { return m_opacity; }

	private:
		int m_time;
		int m_w;
		int m_h;
		int m_x;
		int m_y;
		qreal m_accel;
		int m_velocity;
		qreal m_opacity;
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
		ALyxAnimation(QObject * parent = 0, ALyxControl * control = 0);
		~ALyxAnimation();

		ALyxAnimationStops	stops;

		//! \brief Starts the animation.
		void start();
		
		//! \brief Start the animation from the end to the begining.
		void reverse();
		
		//! \brief Sets the animation time in ticks.
		void setAnimationTime(int ticks) { m_totalAnimationTime = ticks; }

	private:
		ALyxControl *m_control;

		int m_totalAnimationTime;
		bool m_reverse;

		int m_currentAnimationStop;
		int m_currentTime;

		QTimer *timer;

	public slots:
		void animateStep();
};

#endif
