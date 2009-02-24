/*
 * Copyright (C) 2008 Pavlov Denis
 *
 * Volume control module.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or any later version.
 *
*/

#ifndef __DEFAULT_HOME_H__
#define __DEFAULT_HOME_H__

#include <QtGui>
#include <QPushButton>

#include "../../panel.h"
#include "../../buttons.h"
#include "../../skinner.h"
#include "../../m_interface.h"

class homeModuleWidget : public QWidget {
    Q_OBJECT
    public:
	/* public members */
	homeModuleWidget(QWidget * parent = 0, ASkinner *s = 0);
	~homeModuleWidget();

	void setSkinner(ASkinner *s) { m_skinner = s; }

    private:
	/* private members */
	ASkinner * m_skinner;

    private slots:
};

class homeModuleApplet : public QWidget {
	Q_OBJECT
	public:
		/* public members */
		homeModuleApplet(QWidget * parent = 0, ASkinner *s = 0);
		~homeModuleApplet();

		void setSkinner(ASkinner *s) { m_skinner = s; }

	private:
		/* private members */
		ASkinner * m_skinner;

	private slots:
};

class homeModule : public QObject, M_Interface {
	Q_OBJECT
	Q_INTERFACES(M_Interface)

	public:
		QWidget * activate(QWidget * parent = 0);
		QWidget * activateApplet(QWidget * parent = 0);

	private:
		homeModuleApplet * appletWidget;
};

#endif
