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

#ifndef __M_INTERFACE_H__
#define __M_INTERFACE_H__

#include <QWidget>
#include "panel.h"

class M_Interface {
	public:
		QWidget *moduleWindow;
//		virtual ~M_Interface() {}
		virtual void activate(QWidget *parent = 0);
		virtual void activatePeriodically(QWidget *parent = 0);
		virtual void appendToPanel(APanel *panel = 0, int position = 0);

};

Q_DECLARE_INTERFACE(M_Interface, "com.trolltech.Plugin.M_Interface/1.0"); 

#endif
