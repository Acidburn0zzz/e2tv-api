#ifndef DAILYSOURCE_H
#define DAILYSOURCE_H

#include "source.h"

class DailySource : public Source
{
public:
	DailySource(QJsonObject dailyObject, QString g);

	Source::Kind kind;
	QString name;
	QString quality;
	QString url;
	QString num;

	virtual QJsonObject toJSON();
	virtual Kind getKind() { return kind; }
	virtual QString getServiceName() { return "Daily TV Torrents"; }
	virtual QString getName() { return "Torrent"; }
};

#endif // DAILYSOURCE_H
