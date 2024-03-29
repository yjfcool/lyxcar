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

#ifndef PHONON_VLC_EFFECTMANAGER_H
#define PHONON_VLC_EFFECTMANAGER_H

#include <phonon/effectinterface.h>
#include <phonon/effectparameter.h>

#include <vlc/vlc.h>

#include <QtCore/QObject>

namespace Phonon
{
namespace VLC
{

class EffectInfo
{
public:

	enum Type
	{
		AudioEffect,
		VideoEffect
	};

	EffectInfo( const QString & n, int i_filt, Type t, const QString &desc = "", const QString &auth = "" )
	{
		name = n;
		i_filter = i_filt;
		type = t;
		description = desc;
		author = auth;
	}

	QString getName() const { return name; }
	QString getDescription() const	{ return description; }
	QString getAuthor() const	{ return author; }
	int getFilter() const { return i_filter; }
	Type getType() const { return type; }

private:

	QString name, description, author;
	int i_filter;
	Type type;
};


class EffectManager : public QObject
{
	Q_OBJECT
public:

	EffectManager( QObject *p_parent );
	~EffectManager();

	QList<EffectInfo *> getEffectList() const;
	QList<EffectInfo *> getAudioEffectList() const;
	QList<EffectInfo *> getVideoEffectList() const;

private:

	QList<EffectInfo *> effectList;
	QList<EffectInfo *> audioEffectList;
	QList<EffectInfo *> videoEffectList;
    bool b_equalizer_enabled;

    void updateEffectList();
};

}}	//Namespace Phonon::VLC

#endif	//PHONON_VLC_EFFECTMANAGER_H
