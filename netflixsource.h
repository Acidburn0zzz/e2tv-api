#ifndef NETFLIXSOURCE_H
#define NETFLIXSOURCE_H

#include <QJsonObject>
#include "source.h"

class NetflixSource : public Source
{
public:	
	NetflixSource(QJsonObject netflixObject);

	Source::Kind kind;
	QString name;
	QString service;

	virtual QJsonObject toJSON();
	virtual Kind getKind() { return kind; }
	virtual QString getServiceName() { return service; }
	virtual QString getName() { return "Netflix"; }
};

#endif // NETFLIXSOURCE_H
