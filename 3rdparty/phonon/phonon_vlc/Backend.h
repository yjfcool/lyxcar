/*
 * VLC backend for the Phonon library
 * Copyright (C) 2007-2008  Tanguy Krotoff <tkrotoff@gmail.com>
 *               2008       Lukas Durfina <lukas.durfina@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef PHONON_VLC_BACKEND_H
#define PHONON_VLC_BACKEND_H

#include <phonon/objectdescription.h>
#include <phonon/backendinterface.h>

#include <QtCore/QList>
#include <QtCore/QPointer>
#include <QtCore/QStringList>
#include <QtCore/QObject>

#include "DeviceManager.h"
#include "AudioOutput.h"

#ifdef MAKE_PHONON_VLC_LIB /* We are building this library */
# define PHONON_VLC_EXPORT Q_DECL_EXPORT
#else /* We are using this library */
# define PHONON_VLC_EXPORT Q_DECL_IMPORT
#endif

namespace Phonon
{
namespace VLC
{

class EffectManager;

class Backend : public QObject, public BackendInterface 
{
	Q_OBJECT
	Q_INTERFACES( Phonon::BackendInterface )
public:

	Backend( QObject * p_parent = NULL, const QVariantList & args = QVariantList() );
	~Backend();

	QObject * createObject( BackendInterface::Class, QObject * p_parent, const QList<QVariant> & args );
	DeviceManager *getDeviceManager() { return p_deviceManager; }

	bool supportsVideo() const;
	bool supportsOSD() const;
	bool supportsFourcc( quint32 fourcc ) const;
	bool supportsSubtitles() const;

	void freeSoundcardDevices();

	QList<int> objectDescriptionIndexes( ObjectDescriptionType type ) const;
	QHash<QByteArray, QVariant> objectDescriptionProperties( ObjectDescriptionType type, int i_index ) const;

	bool startConnectionChange( QSet<QObject *> nodes );
	bool connectNodes( QObject * p_source, QObject * p_sink );
	bool disconnectNodes( QObject * p_source, QObject * p_sink );
	bool endConnectionChange( QSet<QObject *> nodes );

public slots:

	/**
	 * @see http://en.wikipedia.org/wiki/Mime_type
	 */
	QStringList availableMimeTypes() const;

	/**
	 * Test of introspection.
	 */
	QString toString() const;

signals:

	void objectDescriptionChanged( ObjectDescriptionType );

private:

	mutable QStringList supportedMimeTypes;
	QList<QPointer<AudioOutput> > audioOutputs;

	EffectManager * p_effectManager;
	DeviceManager * p_deviceManager;
};

}}	//Namespace Phonon::VLC

#endif	//PHONON_VLC_BACKEND_H
