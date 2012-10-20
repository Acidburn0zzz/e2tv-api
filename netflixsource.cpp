#include "netflixsource.h"
#include <QJsonArray>

NetflixSource::NetflixSource(QJsonObject netflixObject) : kind(INVALID)
{
	QJsonArray availArray = netflixObject["availabilities"].toArray();

	for (auto val : availArray)
	{
		QJsonObject availObj = val.toObject();
		if (availObj["format"].toString() == "instant")
		{
			kind = STREAM;
			service = "Netflix Instant Watch";
			break;
		}
		if (availObj["format"].toString() == "dvd")
		{
			kind = DVD_RENT;
			service = "Netflix DVD Rent Service";
		}
	}
}

QJsonObject NetflixSource::toJSON()
{
	QJsonObject obj;

	if (kind == INVALID)
	{
		obj.insert("invalid_source", QString("invalid_source"));
		return obj;
	}

	obj.insert("name",  getName());
	obj.insert("service", getServiceName());
	obj.insert("kind", kindToStr(kind));
	return obj;
}
