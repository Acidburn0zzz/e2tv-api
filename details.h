#ifndef DETAILS_H
#define DETAILS_H

#include <QObject>
#include "demand.h"

class Details : public QObject
{
	Q_OBJECT
public:
	explicit Details(const Demand& demand, QObject *parent = 0);

	void execute();

	QString query;
	
signals:
	
public slots:
	
};

#endif // DETAILS_H
