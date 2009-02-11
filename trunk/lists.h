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

#include <QWidget>

#include "skinner.h"

//! \brief This class implements skinned listbox for LyxCar.
class ALyxListBox : public QWidget {
	Q_OBJECT
	public:

		//! \brief Constructs listbox with the skin specified by s
		/*!
			\param parent is a parent widget
			\param s is an ASkinner object
		*/
		ALyxListBox(QWidget *parent = 0, ASkinner *s = 0);
		~ALyxListBox();
		
	private:
		void drawFrame();

	protected:
		void paintEvent(QPaintEvent *e);
};
