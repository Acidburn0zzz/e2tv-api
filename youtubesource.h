#ifndef YOUTUBESOURCE_H
#define YOUTUBESOURCE_H

#include "source.h"

class YoutubeSource : public Source
{
public:
	YoutubeSource(QJsonObject youtubeObject);

	Source::Kind kind;
	QString url;

	virtual QJsonObject toJSON();
	virtual Kind getKind() { return kind; }
	virtual QString getServiceName() { return "youtube"; }
	virtual QString getName() { return "Trailer"; }
};

#endif // YOUTUBESOURCE_H
