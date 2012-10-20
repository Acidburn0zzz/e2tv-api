#ifndef SEARCH_H
#define SEARCH_H

#include <QObject>
#include <QUrl>
#include <QNetworkReply>

class Demand;

class Search : public QObject
{
	Q_OBJECT
public:
	explicit Search(const Demand& demand, QObject *parent = 0);

	void execute();

	QString query;
	QUrl url;
	
signals:
	
public slots:
	void replyFinished(QNetworkReply* reply);
};

#endif // SEARCH_H
