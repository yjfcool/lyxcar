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

#include "VideoWidget.h"

#include "MediaObject.h"
#include "VLCMediaObject.h"

#include "vlc_loader.h"

#include <QtGui/QWidget>
#include <QtGui/QApplication>
#include <QtGui/QDesktopWidget>
#include <QtCore/QtDebug>

namespace Phonon
{
namespace VLC
{

VideoWidget::VideoWidget( QWidget *p_parent )
	: SinkNode( p_parent )
{
	p_video_widget = new Widget( p_parent );

	aspect_ratio = Phonon::VideoWidget::AspectRatioAuto;
	scale_mode = Phonon::VideoWidget::FitInView;

    b_filter_adjust_activated = false;
	f_brightness = 0.0;
	f_contrast = 0.0;
	f_hue = 0.0;
	f_saturation = 0.0;
}

VideoWidget::~VideoWidget()
{
}

void VideoWidget::connectToMediaObject(PrivateMediaObject *mediaObject)
{
	SinkNode::connectToMediaObject( mediaObject );

	connect( mediaObject, SIGNAL( videoWidgetSizeChanged( int, int ) ),
		                  SLOT( videoWidgetSizeChanged( int, int ) ) );

	mediaObject->setVideoWidgetId( (int) p_video_widget->winId() );
}

Phonon::VideoWidget::AspectRatio VideoWidget::aspectRatio() const
{
	return aspect_ratio;
}

void VideoWidget::setAspectRatio( Phonon::VideoWidget::AspectRatio aspect )
{
	//For VLC:
	//Accepted formats are x:y (4:3, 16:9, etc.) expressing the global image aspect.

    // finish if no player
	if( !p_vlc_current_media_player )
        return;

	aspect_ratio = aspect;

	switch ( aspect_ratio )
	{
        //Let the decoder find the aspect ratio automatically from the media file (this is the default).
        case Phonon::VideoWidget::AspectRatioAuto:
            //p_libvlc_video_set_aspect_ratio( p_vlc_current_media_player, "", p_vlc_exception );
            checkException();
            break;

        //Fits the video into the widget making the aspect ratio depend solely on the size of the widget.
        //This way the aspect ratio is freely resizeable by the user.
        case Phonon::VideoWidget::AspectRatioWidget:
            //p_libvlc_video_set_aspect_ratio( p_vlc_current_media_player, "", p_vlc_exception );
            checkException();
            break;

        case Phonon::VideoWidget::AspectRatio4_3:
            //p_libvlc_video_set_aspect_ratio( p_vlc_current_media_player, "4:3", p_vlc_exception );
            checkException();
            break;

        case Phonon::VideoWidget::AspectRatio16_9:
            //p_libvlc_video_set_aspect_ratio( p_vlc_current_media_player, "16:9", p_vlc_exception );
            checkException();
            break;

        default:
            qCritical() << __FUNCTION__ << "error: unsupported AspectRatio:" << ( int ) aspect_ratio;
	}
}

Phonon::VideoWidget::ScaleMode VideoWidget::scaleMode() const
{
	return scale_mode;
}

void VideoWidget::setScaleMode( Phonon::VideoWidget::ScaleMode scale )
{
	//The ScaleMode enum describes how to treat aspect ratio during resizing of video

	scale_mode = scale;

	switch ( scale_mode ) 
	{
        //The video will be fitted to fill the view keeping aspect ratio
        case Phonon::VideoWidget::FitInView:
            break;

        //The video is scaled
        case Phonon::VideoWidget::ScaleAndCrop:
            break;

        default:
            qWarning() << __FUNCTION__
                       << "unknow Phonon::VideoWidget::ScaleMode:"
                       << scale_mode;
	}
}

qreal VideoWidget::brightness() const 
{
	return f_brightness;
}

void VideoWidget::setBrightness( qreal brightness )
{
	f_brightness = brightness;

    // vlc takes brightness in range 0.0 - 2.0
	if( p_vlc_current_media_player )
	{
	    if ( !b_filter_adjust_activated )
	    {
	        //p_libvlc_video_filter_add(p_vlc_current_media_player, ADJUST, p_vlc_exception);
	        //checkException();
	        b_filter_adjust_activated = true;
	    }
		//p_libvlc_video_set_brightness( p_vlc_current_media_player, f_brightness + 1.0, p_vlc_exception );
		//checkException();
	}
}



qreal VideoWidget::contrast() const
{
	return f_contrast;
}

void VideoWidget::setContrast( qreal contrast )
{
	f_contrast = contrast;

    // vlc takes contrast in range 0.0 - 2.0
    float f_contrast = contrast;
	if( p_vlc_current_media_player )
	{
	    if ( !b_filter_adjust_activated )
	    {
	        //p_libvlc_video_filter_add( p_vlc_current_media_player, ADJUST, p_vlc_exception );
	        //checkException();
	        b_filter_adjust_activated = true;
	    }
		//p_libvlc_video_set_contrast( p_vlc_current_media_player, f_contrast + 1.0, p_vlc_exception );
		//checkException();
	}
}

qreal VideoWidget::hue() const
{
	return f_hue;
}

void VideoWidget::setHue(qreal hue)
{
	f_hue = hue;

    // vlc takes hue in range 0 - 360 in INT
    int i_hue = ( f_hue + 1.0 ) * 180;
	if( p_vlc_current_media_player )
	{
	    if ( !b_filter_adjust_activated )
	    {
	        //p_libvlc_video_filter_add(p_vlc_current_media_player, ADJUST, p_vlc_exception);
	        //checkException();
	        b_filter_adjust_activated = true;
	    }
		//p_libvlc_video_set_hue( p_vlc_current_media_player, i_hue, p_vlc_exception );
		//checkException();
	}

}

qreal VideoWidget::saturation() const
{
	return f_saturation;
}

void VideoWidget::setSaturation( qreal saturation )
{
	f_saturation = saturation;

    // vlc takes brightness in range 0.0 - 3.0
	if( p_vlc_current_media_player )
	{
	    if ( !b_filter_adjust_activated )
	    {
	       // p_libvlc_video_filter_add(p_vlc_current_media_player, ADJUST, p_vlc_exception);
	        //checkException();
	        b_filter_adjust_activated = true;
	    }
		//p_libvlc_video_set_saturation(p_vlc_current_media_player, ( f_saturation + 1.0 ) * 1.5, p_vlc_exception);
		//checkException();
	}
}

Widget * VideoWidget::widget()
{
	return p_video_widget;
}

void VideoWidget::videoWidgetSizeChanged(int i_width, int i_height)
{
	qDebug() << __FUNCTION__ << "video width" << i_width
	                         << "height:" << i_height;

	//It resizes dynamically the widget + the main window
	//I didn't find another way

	QSize videoSize( i_width, i_height );
	videoSize.boundedTo( QApplication::desktop()->availableGeometry().size() );

	p_video_widget->hide();
	p_video_widget->setVideoSize( videoSize );
#ifdef Q_OS_WIN
    QWidget *p_parent = qobject_cast<QWidget *>( this->parent() );
	QSize previousSize = p_parent->minimumSize();
	p_parent->setMinimumSize( videoSize );
#endif
	p_video_widget->show();
#ifdef Q_OS_WIN
	p_parent->setMinimumSize( previousSize );
#endif
}

}}	//Namespace Phonon::VLC
