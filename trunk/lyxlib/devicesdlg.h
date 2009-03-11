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

		//! Adds a device entry to devices list.
		void addDevice(QString path, QString name, QPixmap icon);

		//! Get active device item.
		ALyxListWidgetItem * activeDeviceItem();

		//! Get active device filesystem path
		QString activeDevicePath();

		//! Get active device title
		QString activeDeviceName();

		//! Sets active device by filesystem path
		void setActiveDeviceByPath(QString path);

		//! Sets active device by device name. <b>UNIMPLEMENTED</b>
		void setActiveDeviceByName(QString name);

		//! Clears devices list in dialog
		void clear();
	private:
		// Device name - Device path
		QMap<ALyxListWidgetItem *, QString>	m_devices;

		ALyxJogdial *m_jogdial;
};

#endif
