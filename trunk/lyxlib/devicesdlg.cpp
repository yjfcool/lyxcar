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

	m_jogdial = new ALyxJogdial(this);
	m_jogdial->move(95, 60);
	m_jogdial->setFixedSize(210, 130);
	m_jogdial->show();
}

void ALyxDevicesDialog::clear() {
 	m_devices.clear();
	m_jogdial->clear();
}

ALyxListWidgetItem * ALyxDevicesDialog::activeDeviceItem() {
        return m_jogdial->activeItem();
}

QString ALyxDevicesDialog::activeDevicePath() {
	return m_devices.value(m_jogdial->activeItem());
}

QString ALyxDevicesDialog::activeDeviceName() {
	return m_jogdial->activeItem()->text();
}

void ALyxDevicesDialog::setActiveDeviceByPath(QString path) {
	ALyxListWidgetItem *item = m_devices.key(path);
	m_jogdial->setActiveItem(item);
}

void ALyxDevicesDialog::setActiveDeviceByName(QString name) {

}

void ALyxDevicesDialog::addDevice(QString path, QString name, QPixmap icon) {
	ALyxListWidgetItem *item = new ALyxListWidgetItem(m_jogdial, name, icon);
	item->setTextColor(QColor("white"));
	m_jogdial->addItem(item);
	m_devices.insert(item, path);
}

ALyxDevicesDialog::~ALyxDevicesDialog() {
	qDebug() << "ALyxDevicesDialog destroyed";
}
