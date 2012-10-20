#include "details.h"
#include "demand.h"

Details::Details(const Demand &demand, QObject *parent) :
	QObject(parent), query(demand.query)
{
}

void Details::execute()
{
}
