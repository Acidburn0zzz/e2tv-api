#include "sources.h"
#include "netflixsource.h"
#include "trailersource.h"
#include <iostream>
#include <QCoreApplication>
#include <QJsonArray>
#include <QDebug>

Sources::Sources(const Demand &demand, QObject *parent) :
	QObject(parent), query(demand.query), type(INVALID),
	url_freebase("https://www.googleapis.com/freebase/v1/mqlread"),
	url_movies("http://api.movies.io/movies/search")
{
	for (const QString& opt : demand.options)
	{
		if (opt == "--film" && type == INVALID)
			type = FILM;
		else if (opt == "--tv" && type == INVALID)
			type = TV;
	}
}

void Sources::execute()
{
	execute_freebase();
}

void Sources::execute_freebase()
{
	url_freebase.addQueryItem("indent", "2");
	url_freebase.addQueryItem("query", R"*([{ "mid": ")*" + query + R"*(", "name": null, "type": "/film/film" }])*");

	QNetworkAccessManager* manager = new QNetworkAccessManager(this);
	connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished_freebase(QNetworkReply*)));
	manager->get(QNetworkRequest(url_freebase));
}

void Sources::execute_movies(QString title)
{
	url_movies.addQueryItem("q", title);

	QNetworkAccessManager* manager = new QNetworkAccessManager(this);
	connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished_movies(QNetworkReply*)));
	manager->get(QNetworkRequest(url_movies));
}


void Sources::done(QJsonDocument jsonDoc)
{
	std::wcout << QString::fromUtf8(jsonDoc.toJson()).toStdWString();
	qApp->exit();
}

void Sources::replyFinished_freebase(QNetworkReply *reply)
{
	if (reply->error() != QNetworkReply::NoError)
	{
		QJsonObject obj;
		obj.insert("network_error", reply->errorString());
		done(QJsonDocument(obj));
	}
	QJsonDocument jsonDoc = QJsonDocument::fromJson(reply->readAll());
	QString title = jsonDoc.object()["result"].toArray().first().toObject()["name"].toString();

	execute_movies(title);
}

void Sources::replyFinished_movies(QNetworkReply *reply)
{
	if (reply->error() != QNetworkReply::NoError)
	{
		QJsonObject obj;
		obj.insert("network_error", reply->errorString());
		done(QJsonDocument(obj));
	}
	QJsonDocument jsonDoc = QJsonDocument::fromJson(reply->readAll());

	QJsonArray moviesArray = jsonDoc.object()["movies"].toArray();
	if (moviesArray.empty())
	{
		QJsonObject obj;
		obj.insert("error", QString("no such film on movies.io"));
		done(QJsonDocument(obj));
	}

	QJsonObject movieObj = moviesArray.first().toObject();

	if (movieObj.contains("trailer"))
		sources.append(new TrailerSource(movieObj["trailer"].toObject()));
//	QString trailer_provider = movieObj["trailer"].toObject()["provider"].toString();
//	QString trailer = movieObj["trailer"].toObject()["url"].toString();
//	qDebug() << trailer_provider << trailer;

	if (movieObj["sources"].toObject().contains("netflix"))
		sources.append(new NetflixSource(movieObj["sources"].toObject()["netflix"].toObject()));


	QJsonArray ret;

	for (Source* source : sources)
	{
		ret.append(source->toJSON());
	}

	QJsonDocument sourcesDoc(ret);
	done(sourcesDoc);

}
