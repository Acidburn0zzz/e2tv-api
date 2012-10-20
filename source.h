#ifndef SOURCE_H
#define SOURCE_H

#include <QString>
#include <QJsonObject>

class Source
{
public:

	enum Kind { INVALID, LIVE_TV, PAY, STREAM, TORRENT, DVD_RENT, TRAILER };
	static QString kindToStr(Kind k);

	Source();

	virtual QJsonObject toJSON() = 0;
	virtual Kind getKind() = 0;
	virtual QString getName() = 0;
	virtual QString getServiceName() = 0;

	virtual bool provideWebLink() { return false; }
	virtual QString getWebLink() { return  ""; }
};

#endif // SOURCE_H
