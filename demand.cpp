#include "demand.h"
#include "search.h"
#include "details.h"
#include "sources.h"
#include "channels.h"

#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>
#include <iostream>
#include <QCoreApplication>

Demand::Demand() : method(INVALID)
{
}

Demand Demand::fromArguments(QStringList arguments)
{
	Demand demand;

	arguments.removeFirst();

	if (arguments.empty())
		qApp->exit();

	if (arguments.first() == "--search")
		demand.method = SEARCH;
	else if (arguments.first() == "--details")
		demand.method = DETAILS;
	else if (arguments.first() == "--sources")
		demand.method = SOURCES;
	else if (arguments.first() == "--channels")
		demand.method = CHANNELS;
	else
		return demand;

	arguments.removeFirst();

	for (const QString& arg : arguments)
	{
		if (arg.startsWith("--"))
			demand.options.append(arg);
		else if (demand.query.isEmpty())
			demand.query = arg;
	}

	return demand;
}

void Demand::execute()
{
	if (method == SEARCH)
	{
		Search* search = new Search(*this);
		search->execute();
	}
	else if (method == DETAILS)
	{
		Details* details = new Details(*this);
		details->execute();
	}
	else if (method == SOURCES)
	{
		Sources* sources = new Sources(*this);
		sources->execute();
	}
	else if (method == CHANNELS)
	{
		Channels* channels = new Channels;
		channels->execute();
	}
	else
	{
		QJsonObject obj;
		obj.insert("error", QString("invalid method"));
		QJsonDocument doc(obj);
		std::wcout << QString::fromUtf8(doc.toJson()).toStdWString();
		qApp->exit();
		return;
	}
}
