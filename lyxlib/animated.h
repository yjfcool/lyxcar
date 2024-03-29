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
//! It defines the state of a control (position, size and opacity) at time defined by \param time.
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
		//! \brief Creates new time stop for animation.
		/*!
			\param time is a time in ticks in which this animation time stop reaches. Other words this is a position of the stop in a timeline.
			\param x is a left coordinate of a control.
			\param y is a left coordinate of a control.
			\param w is a width of a control.
			\param h is a height of a control.
			\param opacity is a total opacity of the control.
			\param accel UNUSED YET
			\param velo UNUSED YET

			Size, position and opacity of a control at the time stop is set once when object is created.
		*/
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

		//! \brief Returns X position of an animated widget at a time stop.
		int x() { return m_x; }
		//! \brief Returns Y position of an animated widget at a time stop.
		int y() { return m_y; }
		//! \brief Returns the width of an animated widget at a time stop.
		int width() { return m_w; }
		//! \brief Returns the height of an animated widget at a time stop.
		int height() { return m_h; }
		//! \brief Returns time of time stop.
		int time() { return m_time; }
		//! \brief Returns the opacity of an animated widget at a time stop.
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
//! Controls are animated through ALyxAnimationStop time stops.
//! There are two types of transformations of a control: moving and blending.
//! Every animation going between two time stops goes as a linear transformation
//! with a given velocity and coordinates. In other words, when the control transforms
//! it's size from 0,0 to 100,100 in 50ms, and the transformation is defined by 2 time stops
//! it changes regularly by 20 pixels in 1ms.
class ALyxAnimation : public QObject {
	Q_OBJECT
	public:
		//! \brief Create new abstract animation object.
		//! This object can animate any ALyxControl derived visual controls.
		/*!
			\param parent is a parent of this animation.
			\param control is a pointer to Lyx control to animate.
		*/
		ALyxAnimation(QObject * parent = 0, ALyxControl * control = 0);
		~ALyxAnimation();

		//! \brief QList of an animation stops.
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
		//! \brief Goes animation one step forward or backward.
		void animateStep();
		
	signals:
		//! \brief Emitted when the animation queue is started.
		void started();
		//! \brief Emitted when the animation queue is stopped.
		void finished();
		//! \brief Emitted every time the animation queue reaches next time stop.
		void stopReached(ALyxAnimationStop *);
};

#endif
