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

#include "vlc_loader.h"

#include <QtCore/QCoreApplication>
#include <QtCore/QLibrary>
#include <QtCore/QtDebug>
#include <QtCore/QStringList>
#include <QtCore/QDir>
#include <QtCore/QSettings>
#include <QtCore/QtGlobal>

#include <QtGui/QWidget>

//Global variables
libvlc_instance_t * p_vlc_instance = NULL;
libvlc_exception_t * p_vlc_exception = new libvlc_exception_t();
libvlc_media_player_t * p_vlc_current_media_player = NULL;

namespace Phonon
{
namespace VLC
{

void initLibVLC()
{
	//Global variables
	p_vlc_instance = NULL;
	p_vlc_exception = new libvlc_exception_t();

	//Complete list of VLC command line options:
	//http://wiki.videolan.org/VLC_command-line_help
	const char * vlcArgc[] = {
		getVLCPath().toAscii().constData(),
		"--plugin-path=", getVLCPluginsPath().toAscii().constData(),
#ifdef CMAKE_CXX_FLAGS_DEBUG
        "-vvv",
#else
        "-vvv",
#endif
		"--intf=dummy",
		"--no-media-library",
		"--no-one-instance",
		"--reset-plugins-cache",
		"--no-stats",
		"--no-osd",
		"--no-video-title-show"
	};

	libvlc_exception_init( p_vlc_exception );

	//Init VLC modules, should be done only once
	p_vlc_instance = libvlc_new( sizeof( vlcArgc ) / sizeof( *vlcArgc ), vlcArgc, p_vlc_exception );
	checkException();

	//FIXME Cannot do that: otherwise does not load VLC plugins
	//changeBackToCurrentDirectory();

	qDebug() << "Using VLC version:" << libvlc_get_version();
	qDebug() << "VLC loaded";
}

void releaseLibVLC()
{
	libvlc_release( p_vlc_instance );
	unloadLibVLC();
}

void checkException()
{
	if( libvlc_exception_raised( p_vlc_exception ) )
	{
		qDebug() << "libvlc exception:" << libvlc_exception_get_message( p_vlc_exception );
		libvlc_exception_clear( p_vlc_exception );
	}
}

#ifdef Q_OS_WIN
	#include <windows.h>

	char currentDirectory[MAX_PATH];
#endif	//Q_OS_WIN

static QLibrary * p_libvlc_control = NULL;

/**
 * Only under Windows.
 *
 * Use Win32 API function: GetCurrentDirectory()
 *
 * @see setCurrentDirectory()
 * @see changeBackToCurrentDirectory()
 */
void saveCurrentDirectory()
{
#ifdef Q_OS_WIN
	DWORD dwRet = GetCurrentDirectoryA( MAX_PATH, currentDirectory );
	if ( dwRet == 0 || dwRet > MAX_PATH )
	{
		qFatal("GetCurrentDirectory() failed (%d)", GetLastError());
	}
#endif	//Q_OS_WIN
}

/**
 * Only under Windows.
 *
 * Use Win32 API function: SetCurrentDirectory()
 *
 * @see saveCurrentDirectory()
 * @see changeBackToCurrentDirectory()
 */
void setCurrentDirectory( const char * dir )
{
#ifdef Q_OS_WIN
	//Change current directory in order to load all the *.dll (libvlc.dll + all the plugins)
	if( !SetCurrentDirectoryA( dir ) )
	{
		qFatal( "SetCurrentDirectory() failed (%d)\n", GetLastError() );
	}
#endif	//Q_OS_WIN
}

QString getVLCPath() {
	static const char *psz_libvlc_control_name = "libvlc";
	static const char *psz_libvlc_control_functionToTest = "libvlc_exception_init";

	static QString libvlc_path;

	if( !libvlc_path.isEmpty() )
	{
		return libvlc_path;
	}

	//Tries to autodetect the VLC path with a default list of path

	QStringList pathList;
	pathList << QCoreApplication::libraryPaths();

#ifdef Q_OS_LINUX
	pathList << "/usr/local/lib";
#endif	//Q_OS_LINUX

#ifdef Q_OS_WIN
	static const char *psz_libvlc_version = "0.9";

	saveCurrentDirectory();

	//QSettings allows us to read the Windows registry
	//Check if there is a standard VLC installation under Windows
	//If there is a VLC Windows installation, check we get the good version i.e 0.9
	QSettings settings( QSettings::SystemScope, "VideoLAN", "VLC" );
	if( settings.value("Version").toString().contains( psz_libvlc_version ) )
	{
		QString vlcInstallDir = settings.value("InstallDir").toString();
		pathList << vlcInstallDir;

		setCurrentDirectory( vlcInstallDir.toAscii().constData() );
	}
#endif	//Q_OS_WIN

	p_libvlc_control = new QLibrary();
	foreach ( libvlc_path, pathList )
	{
		p_libvlc_control->setFileName( libvlc_path + QDir::separator() + psz_libvlc_control_name );

		if( p_libvlc_control->load() && p_libvlc_control->resolve( psz_libvlc_control_functionToTest ) )
		{
			qDebug() << "VLC path found:" << libvlc_path;
			return libvlc_path;
		}
		qDebug() << "Warning:" << p_libvlc_control->errorString();
	}

	unloadLibVLC();
	qFatal(" Cannot find '%s' on your system", psz_libvlc_control_name );
	return libvlc_path;
}

void changeBackToCurrentDirectory()
{
#ifdef Q_OS_WIN
	//Change back current directory
	if( !SetCurrentDirectoryA(currentDirectory) )
	{
		qFatal("SetCurrentDirectory() failed (%d)\n", GetLastError());
	}
#endif	//Q_OS_WIN
}

QString getVLCPluginsPath()
{
	QString vlcPath = getVLCPath();

#ifdef Q_OS_WIN
	QString vlcPluginsPath( vlcPath + "/plugins" );
#endif	//Q_OS_WIN

#ifdef Q_OS_LINUX
	QString vlcPluginsPath( vlcPath + "/vlc" );
#endif	//Q_OS_LINUX

	qDebug() << "VLC plugins path:" << vlcPluginsPath;

	return vlcPluginsPath;
}

void unloadLibVLC()
{
	p_libvlc_control->unload();
	delete p_libvlc_control;
	p_libvlc_control = NULL;
}


}}	//Namespace Phonon::VLC
