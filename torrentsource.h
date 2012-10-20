#ifndef TORRENTSOURCE_H
#define TORRENTSOURCE_H

#include "source.h"

class TorrentSource : public Source
{
public:
	TorrentSource(QJsonObject torrentObject);

	Source::Kind kind;
	QString name;
	QString quality;
	QString magnet;
	int seed, size;
	QString filename;
	QString img;

	virtual QJsonObject toJSON();
	virtual Kind getKind() { return kind; }
	virtual QString getServiceName() { return "Torrent"; }
	virtual QString getName() { return "Torrent"; }

};

#endif // TORRENTSOURCE_H
