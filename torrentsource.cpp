#include "torrentsource.h"

TorrentSource::TorrentSource(QJsonObject torrentObject) : kind(TORRENT)
{
	seed = torrentObject["seeders"].toDouble();
	size = torrentObject["size"].toDouble();
	quality = torrentObject["quality"].toString();
	magnet = torrentObject["magnet"].toString();
}

QJsonObject TorrentSource::toJSON()
{
	QJsonObject obj;

	if (kind == INVALID)
	{
		obj.insert("invalid_source", QString("invalid_source"));
		return obj;
	}

	obj.insert("name", getName());
	obj.insert("service", getServiceName());
	obj.insert("kind", kindToStr(kind));
	obj.insert("url", magnet);
	obj.insert("quality", quality);
	obj.insert("seed", seed);
	obj.insert("size", size);
	return obj;
}
