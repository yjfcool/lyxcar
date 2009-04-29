/*  This file is part of the KDE project.

    Copyright (C) 2007 Trolltech ASA. All rights reserved.

    This library is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 2.1 or 3 of the License.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this library.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "DeviceManager.h"
#include "Backend.h"
//#include "videowidget.h"
//#include "widgetrenderer.h"
#include "vlc_loader.h"

/*
 * This class manages the list of currently
 * active output devices
 */

QT_BEGIN_NAMESPACE

namespace Phonon
{
namespace VLC
{

AudioDevice::AudioDevice( DeviceManager *p_manager, const QByteArray &name_id, const QByteArray &hw_id )
{
    //get an id
    static int counter = 0;
    id = counter++;
    //get name from device
    if( nameId == "default" )
        description = "Default audio device";
    else
    {
        nameId = name_id;
        description = "";
    }
    hwId = hw_id;
}

DeviceManager::DeviceManager( Backend *p_parent )
        : QObject( p_parent )
        , p_backend( p_parent )
{
    updateDeviceList();
}

DeviceManager::~DeviceManager()
{
    audioDeviceList.clear();
}

bool DeviceManager::canOpenDevice( ) const
{
    return true;
}


/*
 * Returns a positive device id or -1 if device
 * does not exist
 */
int DeviceManager::deviceId( const QByteArray &nameId ) const
{
    for( int i = 0 ; i < audioDeviceList.size() ; ++i)
    {
        if( audioDeviceList[i].nameId == nameId )
            return audioDeviceList[i].id;
    }
    return -1;
}

/**
 * Get a human-readable description from a device id
 */
QByteArray DeviceManager::deviceDescription( int i_id ) const
{
    for( int i = 0 ; i < audioDeviceList.size() ; ++i )
    {
        if( audioDeviceList[i].id == i_id )
            return audioDeviceList[i].description;
    }
    return QByteArray();
}

/**
 * Updates the current list of active devices
 */
void DeviceManager::updateDeviceList()
{
    QList<QByteArray> list, list_hw;
    list.append( DEFAULT_ID );
    list_hw.append( "" );

    // get devices from VLC to list
    libvlc_audio_output_t *p_ao_list = libvlc_audio_output_list_get(
             p_vlc_instance, p_vlc_exception);
    checkException();
    libvlc_audio_output_t *p_start = p_ao_list;

    while( p_ao_list )
    {
        list.append( p_ao_list->psz_name );
        list_hw.append( "" );
        p_ao_list = p_ao_list->p_next;
    }
    libvlc_audio_output_list_release( p_start );

    for (int i = 0 ; i < list.size() ; ++i)
    {
        QByteArray nameId = list.at(i);
        QByteArray hwId = list_hw.at(i);
        if( deviceId( nameId ) == -1 )
        {
            // This is a new device, add it
            printf("add aout %s\n", nameId.data() );
            audioDeviceList.append( AudioDevice( this, nameId, hwId ) );
            emit deviceAdded( deviceId( nameId ) );
        }
    }
    if( list.size() < audioDeviceList.size() )
    {
        //a device was removed
        for( int i = audioDeviceList.size() -1 ; i >= 0 ; --i )
        {
            QByteArray currId = audioDeviceList[i].nameId;
            bool b_found = false;
            for( int k = list.size() -1  ; k >= 0 ; --k )
            {
                if( currId == list[k] )
                {
                    b_found = true;
                    break;
                }
            }
            if( !b_found )
            {
                emit deviceRemoved( deviceId( currId ) );
                audioDeviceList.removeAt( i );
            }
        }
    }
}

/**
  * Returns a list of hardware id
  */
const QList<AudioDevice> DeviceManager::audioOutputDevices() const
{
    return audioDeviceList;
}

}
}

QT_END_NAMESPACE
