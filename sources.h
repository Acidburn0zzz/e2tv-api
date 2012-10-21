#ifndef SOURCES_H
#define SOURCES_H

#include <QObject>
#include <QUrl>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include "demand.h"
#include "source.h"

class Sources : public QObject
{
	Q_OBJECT
public:
	enum Type { INVALID, FILM, TV };

	explicit Sources(const Demand &demand, QObject *parent = 0);

	void execute();
	void execute_freebase();
	void execute_movies(QString title);
	void execute_shows(QString title);

	void done(QJsonDocument jsonDoc);

	QString query;
	Type type;
	QString id;

	QUrl url_freebase;
	QUrl url_movies;
	QUrl url_series;

	QList<Source*> sources;
	
signals:
	
public slots:
	void replyFinished_freebase(QNetworkReply* reply);
	void replyFinished_movies(QNetworkReply* reply);
	void replyFinished_series(QNetworkReply* reply);
};

#endif // SOURCES_H
