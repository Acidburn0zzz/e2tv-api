#include "trailersource.h"

TrailerSource::TrailerSource(QJsonObject trailerObject) : kind(TRAILER)
{
	provider = trailerObject["provider"].toString();
	url = trailerObject["url"].toString();
}

QJsonObject TrailerSource::toJSON()
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
	obj.insert("url", getWebLink());
	return obj;
}
