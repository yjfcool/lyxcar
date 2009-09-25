#include "playlist.h"

#include <QDebug>

APlaylist::APlaylist(QString fileName) : QDomDocument() {
	m_root = createElement("playlist");
	appendChild(m_root);

	m_fileName = fileName;
}

void APlaylist::addEntry(QString filePath, QString fileName, QString artist, QString album, QString title) {
	if(!filePath.isEmpty() && !fileName.isEmpty()) {
		QDomElement tag = createElement("entry");
		tag.setAttribute("filePath", filePath);
		tag.setAttribute("fileName", fileName);

		tag.setAttribute("album", album);
		tag.setAttribute("artist", artist);
		tag.setAttribute("title", title);

		m_root.appendChild(tag);
	} else {
		qDebug() << "FilePath or fileName is empty! Can't add.";
	}
}

void APlaylist::addDir(QString dirName) {

}

void APlaylist::addDir(QDir dir) {

}

void APlaylist::removeEntries(QString filePath, QString fileName) {

}

void APlaylist::load(QString fileName) {
	if(fileName.isEmpty()) { fileName = m_fileName; } else { m_fileName = fileName; }
	QFile file(fileName);
	if(!file.open(QIODevice::ReadOnly)) return;
	if(!setContent(&file)) {
		file.close();
		return;
	}
	file.close();
}

void APlaylist::save(QString fileName) {
	if(fileName.isEmpty()) { fileName = m_fileName; } else { m_fileName = fileName; }
	QString playListInText = toString();

	QFile file(fileName);
	if(!file.open(QIODevice::WriteOnly)) return;

	QTextStream out(&file);
	out << playListInText;

	file.close();
}

void APlaylist::clear() {

}
