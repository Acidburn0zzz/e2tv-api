#include "channels.h"
#include <QUrl>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include <QCoreApplication>
#include <iostream>
#include <QDateTime>

Channels::Channels(QObject *parent) :
	QObject(parent)
{
}

void Channels::execute()
{
	QUrl url("http://pgep.francetv.fr/broadcasts?format=json");
	//url.addQueryItem("from", QtD);

	QNetworkAccessManager* manager = new QNetworkAccessManager(this);
	connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
	manager->get(QNetworkRequest(url));
}

void Channels::replyFinished(QNetworkReply *reply)
{
	if (reply->error() != QNetworkReply::NoError)
	{
		QJsonObject obj;
		obj.insert("network_error", reply->errorString());

		QJsonDocument doc(obj);
		std::wcout << QString::fromUtf8(doc.toJson()).toStdWString();
		qApp->exit();
		return;
	}

	QJsonDocument jsonDoc = QJsonDocument::fromJson(reply->readAll());
	qDebug() << jsonDoc.toJson();
}
