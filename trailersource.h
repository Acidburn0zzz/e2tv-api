#ifndef TRAILERSOURCE_H
#define TRAILERSOURCE_H

#include "source.h"

class TrailerSource : public Source
{
public:
	TrailerSource(QJsonObject trailerObject);

	Source::Kind kind;
	QString name;
	QString provider;
	QString url;

	virtual QJsonObject toJSON();
	virtual Kind getKind() { return kind; }
	virtual QString getServiceName() { return provider; }
	virtual QString getName() { return "Trailer"; }

	virtual bool provideWebLink() {return true;}
	virtual QString getWebLink() {return url;}
};

#endif // TRAILERSOURCE_H
