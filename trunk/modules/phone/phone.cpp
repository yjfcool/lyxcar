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

#include "phone.h"
#include "phonewindow.h"

/*
 * Module activation procedure
 */
QWidget * phoneModule::activate(QWidget *parent) {
	moduleWindow = new phoneWindow(parent, m_skinner, m_audioOutput);

	return moduleWindow;
}

void phoneModule::deactivate(QString deactivateFor) {
    emit deactivated(deactivateFor);
}

QWidget * phoneModule::activateApplet(QWidget *parent) {
	return 0;
}

Q_EXPORT_PLUGIN2(phone, phoneModule);
