#include "dailysource.h"

DailySource::DailySource(QJsonObject dailyObject, QString g) : kind(TORRENT)
{
	url = dailyObject[g].toString();
	if (g == "hd")
		quality = "HD";
	else if (g == "720")
		quality = "HD720";
	else if (g == "1080")
		quality = "HD1080";
	num = dailyObject["num"].toString();
}

QJsonObject DailySource::toJSON()
{
	QJsonObject obj;
	obj.insert("name", getName());
	obj.insert("service", getServiceName());
	obj.insert("kind", kindToStr(kind));
	obj.insert("url", url);
	obj.insert("quality", quality);
	obj.insert("num", num);
	return obj;
}
