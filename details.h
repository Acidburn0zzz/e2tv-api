#ifndef DETAILS_H
#define DETAILS_H

#include <QObject>
#include <QUrl>
#include <QNetworkReply>
#include "demand.h"

class Details : public QObject
{
	Q_OBJECT
public:
	enum Type { INVALID, FILM, TV };

	explicit Details(const Demand& demand, QObject *parent = 0);

	void execute();

	QString query;
	QUrl url;
	Type type;
	QString id;
	
signals:
	
public slots:
	void replyFinished(QNetworkReply* reply);
	
};

#endif // DETAILS_H
