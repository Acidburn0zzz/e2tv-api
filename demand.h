#ifndef DEMAND_H
#define DEMAND_H

#include <QString>
#include <QStringList>

class Demand
{
public:
	enum Method { INVALID, SEARCH, DETAILS, SOURCES , CHANNELS };

	Demand();
	void execute();

	static Demand fromArguments(QStringList arguments);

	Method			method;
	QString			query;
	QStringList		options;
};

#endif // DEMAND_H
