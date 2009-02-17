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

#include "home.h"

ALyxHome::ALyxHome(QWidget *parent) {
	lay = new QGridLayout();
	setLayout(lay);
	
	QPushButton *btn1 = new QPushButton("MP3 Player");
	btn1->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	QPushButton *btn2 = new QPushButton("button2");
	btn2->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

	QPushButton *btn3 = new QPushButton("button3");
	btn3->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	QPushButton *btn4 = new QPushButton("button4");
	btn4->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	
	lay->addWidget(btn1, 0, 0);
	lay->addWidget(btn2, 1, 0);
	lay->addWidget(btn3, 0, 1);
	lay->addWidget(btn4, 1, 1);
}

ALyxHome::~ALyxHome() {
	
}
