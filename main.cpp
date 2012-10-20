#include "demand.h"
#include <QCoreApplication>

int main(int argc, char *argv[])
{
	QCoreApplication app(argc, argv);

	Demand demand = Demand::fromArguments(app.arguments());

	demand.execute();
	
	return app.exec();
}
