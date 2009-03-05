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
	ALyxDialog(parent, s) {

	ALyxPushButton *btn = new ALyxPushButton(this, "OK");
	btn->setFont(QFont("Calibri", 16));
	btn->setUpPixmap(QPixmap("./skins/default/button.png"));
	btn->setDownPixmap(QPixmap("./skins/default/button_pushed.png"));

	ALyxPushButton *btn2 = new ALyxPushButton(this, tr("Cancel"));
	btn2->setFont(QFont("Calibri", 16));
	btn2->setUpPixmap(QPixmap("./skins/default/button.png"));
	btn2->setDownPixmap(QPixmap("./skins/default/button_pushed.png"));

	addButton(btn, "ok");
	addButton(btn2, "cancel");
}

void ALyxDevicesDialog::setDevices(ALyxDevicesList devices) {
	m_devices = devices;

	return;
}

ALyxDevicesDialog::~ALyxDevicesDialog() {
	qDebug() << "ALyxDevicesDialog destroyed";
}
