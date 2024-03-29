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

#ifndef PHONON_VLC_WIDGETNOPAINTEVENT_H
#define PHONON_VLC_WIDGETNOPAINTEVENT_H

#include <QtGui/QWidget>

namespace Phonon
{
namespace VLC
{

/**
 * Utility class: special widget for playing videos.
 *
 * Does not handle paintEvent()
 */
class WidgetNoPaintEvent : public QWidget
{
	Q_OBJECT
public:

	WidgetNoPaintEvent( QWidget *p_parent );

	/**
	 * Sets the background color.
	 *
	 * I don't know which one is best: 0x020202 or Qt::black...
	 */
	void setBackgroundColor( const QColor & color );

private:

	void paintEvent( QPaintEvent *p_event );
};

}}	//Namespace Phonon::VLC

#endif	//PHONON_VLC_WIDGETNOPAINTEVENT_H
