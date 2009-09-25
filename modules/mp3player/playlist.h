#ifndef _PLAYLIST_H_
#define _PLAYLIST_H_

#include <QDomDocument>
#include <QFile>
#include <QDir>

class APlaylist : public QDomDocument
{
public:
	APlaylist(QString fileName);

	QString		m_fileName;
	QDomElement	m_root;

	void	addEntry(QString filePath, QString fileName, QString artist = "", QString album = "", QString title = "");
	void	setEntryArtist(QString filePath, QString fileName, QString artist) {}
	void	setEntryAlbum(QString filePath, QString fileName, QString album) {}
	void	setEntryTitle(QString filePath, QString fileName, QString title) {}
	void	updateEntry(QString filePath, QString fileName) {}

	void	addDir(QString dirName);
	void	addDir(QDir dir);
	void	removeEntries(QString filePath, QString fileName);

	void	load(QString fileName);
	void	save(QString fileName = "");
	void	clear();
};

#endif // _PLAYLIST_H_
