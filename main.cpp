#include "demand.h"
#include <QCoreApplication>

int main(int argc, char *argv[])
{
	QCoreApplication app(argc, argv);

	Demand::fromArguments(app.arguments()).execute();
	
	return app.exec();
}
