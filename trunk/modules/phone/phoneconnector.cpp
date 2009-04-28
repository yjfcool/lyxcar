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

#include "phoneconnector.h"

phoneConnector::phoneConnector(QObject *parent) {
    open();
}

phoneConnector::~phoneConnector() {
    m_device->close();
    delete m_device;

    qDebug() << "phoneConnector destroyed";
}

void phoneConnector::open() {
    m_device = new QFile("/dev/ttyACM0");
    if (!m_device->open(QIODevice::ReadWrite | QIODevice::Text)) return;
}

bool phoneConnector::checkPhone() {
    return true;
}

void phoneConnector::run() {
    QTextStream stream(m_device);
    stream << "AT S7=45 S0=0 L1 V1 X4 &c1 E1 Q0";
    QString line = stream.readLine();
    while (!line.isNull()) {
	if(line != "\n") {
	    qDebug() << "phoneConnector:" << line;
	    line = stream.readLine();
	}
    }

    exec();
}
