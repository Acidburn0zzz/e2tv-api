#include "search.h"
#include "demand.h"
#include <QDebug>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QMap>
#include <QCoreApplication>

#include <iostream>

Search::Search(const Demand &demand, QObject *parent) :
	QObject(parent), query(demand.query),
	url("https://www.googleapis.com/freebase/v1/search")
{
	url.addQueryItem("query", query);
	url.addQueryItem("indent", "true");
	url.addQueryItem("prefixed", "true");
	url.addQueryItem("filter", "(any type:/film/film type:/tv/tv_program)");
	url.addQueryItem("mql_output", R"*([{"name": null, "mid":null, "name": [], "type":[]}]")*");
}

void Search::execute()
{
	QNetworkAccessManager* manager = new QNetworkAccessManager(this);
	connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
	manager->get(QNetworkRequest(url));
}

void Search::replyFinished(QNetworkReply *reply)
{
	if (reply->error() != QNetworkReply::NoError)
	{
		QJsonObject obj;
		obj.insert("network_error", reply->errorString());

		QJsonDocument doc(obj);
		std::wcout << QString::fromUtf8(doc.toJson()).toStdWString();
		return;
	}

	QJsonDocument jsonDoc = QJsonDocument::fromJson(reply->readAll());
	QJsonDocument listDoc(jsonDoc.object()["result"].toArray());

	std::wcout << QString::fromUtf8(listDoc.toJson()).toStdWString();
	qApp->exit();
}
