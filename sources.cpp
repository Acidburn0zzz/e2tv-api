#include "sources.h"
#include "netflixsource.h"
#include "torrentsource.h"
#include "trailersource.h"
#include <iostream>
#include <QCoreApplication>
#include <QJsonArray>
#include <QDebug>

Sources::Sources(const Demand &demand, QObject *parent) :
	QObject(parent), query(demand.query), type(INVALID),
	url_freebase("https://www.googleapis.com/freebase/v1/mqlread"),
	url_movies("http://api.movies.io/movies/search"),
	url_series("http://api.dailytvtorrents.org/1.0/episode.getLatest")
{
	url_freebase.addQueryItem("key", "AIzaSyBqWmqxOJglrngvGvUdbcS160y3XCBCaaE");

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

	if (type == FILM)
		url_freebase.addQueryItem("query", R"*([{ "mid": ")*" + query + R"*(", "name": null, "type": "/film/film" }])*");
	else
		url_freebase.addQueryItem("query", R"*([{ "mid": ")*" + query + R"*(", "name": null, "type": "/tv/tv_program" }])*");

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

void Sources::execute_shows(QString title)
{
	url_series.addQueryItem("show_name", title.toLower().replace(" ", "-"));

	QNetworkAccessManager* manager = new QNetworkAccessManager(this);
	connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished_series(QNetworkReply*)));
	manager->get(QNetworkRequest(url_series));
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

	if (type == FILM)
		execute_movies(title);
	else
		execute_shows(title);
		//qDebug() << title.toLower().replace(" ", "-");
}

void Sources::replyFinished_movies(QNetworkReply *reply)
{
	if (reply->error() != QNetworkReply::NoError)
	{
		QJsonObject obj;
		obj.insert("network_error", reply->errorString());
		done(QJsonDocument(obj));
		return;
	}
	QJsonDocument jsonDoc = QJsonDocument::fromJson(reply->readAll());

	QJsonArray moviesArray = jsonDoc.object()["movies"].toArray();
	if (moviesArray.empty())
	{
		QJsonObject obj;
		obj.insert("error", QString("no such film on movies.io"));
		done(QJsonDocument(obj));
		return;
	}

	QJsonObject movieObj = moviesArray.first().toObject();



	if (movieObj.contains("trailer"))
		sources.append(new TrailerSource(movieObj["trailer"].toObject()));

	if (movieObj["sources"].toObject().contains("netflix"))
		sources.append(new NetflixSource(movieObj["sources"].toObject()["netflix"].toObject()));

	if (movieObj["sources"].toObject().contains("torrents"))
	{
		for (auto val : movieObj["sources"].toObject()["torrents"].toArray())
		{
			sources.append(new TorrentSource(val.toObject()));
		}
	}


	QJsonArray ret;

	for (Source* source : sources)
	{
		ret.append(source->toJSON());
	}

	QJsonObject final;
	final.insert("sources", ret);
	final.insert("poster", movieObj["poster"].toObject()["urls"].toObject()["w500"].toString());
	final.insert("bg", movieObj["backdrop"].toObject()["urls"].toObject()["w1280"].toString());

	QJsonDocument sourcesDoc(final);
	done(sourcesDoc);
}

void Sources::replyFinished_series(QNetworkReply *reply)
{
	if (reply->error() != QNetworkReply::NoError)
	{
		QJsonObject obj;
		obj.insert("network_error", reply->errorString());
		done(QJsonDocument(obj));
		return;
	}
	QJsonDocument jsonDoc = QJsonDocument::fromJson(reply->readAll());
	QJsonArray ret;

	QJsonObject ref;
	ref.insert("kind", QString("Torrent"));
	ref.insert("name", QString("Torrent"));
	ref.insert("service", QString("Daily TV Torrents"));
	ref.insert("num", jsonDoc.object()["num"].toString());
	if (!jsonDoc.object()["title"].isNull())
		ref.insert("title", jsonDoc.object()["title"].toString());

	if (!jsonDoc.object()["hd"].isNull())
	{
		QJsonObject hdObj(ref);
		hdObj.insert("quality", QString("HD"));
		hdObj.insert("url", jsonDoc.object()["hd"].toString());
		ret.append(hdObj);
	}
	if (!jsonDoc.object()["720"].isNull())
	{
		QJsonObject hdObj(ref);
		hdObj.insert("quality", QString("HD720"));
		hdObj.insert("url", jsonDoc.object()["720"].toString());
		ret.append(hdObj);
	}
	if (!jsonDoc.object()["1080"].isNull())
	{
		QJsonObject hdObj(ref);
		hdObj.insert("quality", QString("HD1080"));
		hdObj.insert("url", jsonDoc.object()["1080"].toString());
		ret.append(hdObj);
	}
	QJsonObject final;
	final.insert("sources", ret);
	done(QJsonDocument(final));
}
