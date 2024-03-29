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

#include "WidgetNoPaintEvent.h"

#include <QtGui/QPainter>

namespace Phonon
{
namespace VLC
{

WidgetNoPaintEvent::WidgetNoPaintEvent( QWidget *p_parent )
	: QWidget( p_parent )
{
	//When resizing fill with black (backgroundRole color) the rest is done by paintEvent
	setAttribute( Qt::WA_OpaquePaintEvent );

	//Disable Qt composition management as MPlayer draws onto the widget directly
	setAttribute( Qt::WA_PaintOnScreen );

	//Indicates that the widget has no background, i.e. when the widget receives paint events,
	//the background is not automatically repainted.
	setAttribute( Qt::WA_NoSystemBackground );

	//Required for dvdnav
	setMouseTracking( true );
}

void WidgetNoPaintEvent::paintEvent(QPaintEvent *p_event)
{
	//FIXME this makes the video flicker
	//Makes everything backgroundRole color
	QPainter painter( this );
	painter.eraseRect( rect() );
}

void WidgetNoPaintEvent::setBackgroundColor( const QColor & color )
{
	QPalette p = palette();
	p.setColor( backgroundRole(), color );
	setPalette( p );
}

}}	//Namespace Phonon::VLC
