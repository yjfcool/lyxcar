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

#ifndef __PHONECONNECTOR_H__
#define __PHONECONNECTOR_H__

#include <QThread>
#include <QFile>
#include <QTextStream>
#include <QDebug>

class phoneConnector : public QThread {
    Q_OBJECT
    public:
	phoneConnector(QObject *parent);
	~phoneConnector();

	void open();
	void run();

	// Send AT+ command to check phone on comm interface
	// Returns true if there was a correct answer, otherwise returns false.
	bool checkPhone();

    private:
	QString	m_phoneDevice;	// Phone communication device (e.i. /dev/ttyXXXN)
	QString m_phoneAudioDevice; // Phone sound device to connect
	
	QString m_phoneVendor;
	QString m_phoneModel;
	
	QFile *m_device;
};

#endif // __PHONECONNECTOR_H__
