#include "youtubesource.h"
#include "QJsonArray"

YoutubeSource::YoutubeSource(QJsonObject youtubeObject) : kind(TRAILER)
{
	url = youtubeObject["feed"].toObject()["entry"].toArray().first().toObject()["link"].toArray().first().toObject()["href"].toString();
}

QJsonObject YoutubeSource::toJSON()
{
	QJsonObject obj;
	obj.insert("name",  getName());
	obj.insert("service", getServiceName());
	obj.insert("kind", kindToStr(kind));
	obj.insert("url", url);
	return obj;
}
