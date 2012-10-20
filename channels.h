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
	void execute_channels();
	void execute_broadcasts();
	
signals:
	
public slots:
//	void replyFinished_channels(QNetworkReply* reply);
//	void replyFinished_broadcasts(QNetworkReply* reply);
};

#endif // CHANNELS_H
