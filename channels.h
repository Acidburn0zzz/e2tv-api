#ifndef CHANNELS_H
#define CHANNELS_H

#include <QObject>
#include <QNetworkReply>

class Channels : public QObject
{
	Q_OBJECT
public:
	explicit Channels(QObject *parent = 0);

	void execute();
	
signals:
	
public slots:
	void replyFinished(QNetworkReply* reply);
};

#endif // CHANNELS_H
