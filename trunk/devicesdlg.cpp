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

#include "devicesdlg.h"

ALyxDevicesDialog::ALyxDevicesDialog(QWidget *parent, ASkinner *s) :
	ALyxDialog(parent, s) {}

void ALyxDevicesDialog::setDevices(ALyxDevicesList devices) {
	m_devices = devices;

	return;
}

ALyxDevicesDialog::~ALyxDevicesDialog() {
	qDebug() << "ALyxDevicesDialog destroyed";
}
