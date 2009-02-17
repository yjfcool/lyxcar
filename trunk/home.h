/*
 * Copyright (C) 2008 Pavlov Denis
 *
 * Comments unavailable.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or any later version.
 *
*/

#ifndef __HOME_H__
#define __HOME_H__

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>

//! \brief Class for home window with buttons to start modular applications.
class ALyxHome : public QWidget {
	Q_OBJECT

	public:
		ALyxHome(QWidget *parent = 0);
		~ALyxHome();

	private:
		QGridLayout *lay;

};

#endif
