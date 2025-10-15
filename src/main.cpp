#include "Controller.h"
#include "ModelAdapter.h"
#include "View.h"
#include <QtWidgets>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	ModelAdapter model;
	View view;
	Controller controller(model, view);

	controller.Run();

	return app.exec();
}
