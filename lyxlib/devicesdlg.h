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

#ifndef __DEVICESDLG_H__
#define __DEVICESDLG_H__

#include <QWidget>

#include "dialogs.h"
#include "jogdial.h"

typedef QMap<QString,QString> ALyxDevicesList;

class ALyxDevicesDialog : public ALyxDialog {
	Q_OBJECT
	public:
		ALyxDevicesDialog(QWidget *parent = 0, ASkinner *s = 0);
		~ALyxDevicesDialog();

		void setDevices(ALyxDevicesList devices);

	private:
		QMap<QString,QString>	m_devices;
};

#endif
