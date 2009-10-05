#include "ui_shareboard.h"

int main(int argc, char **argv)
{

	QApplication app(argc, argv);
	QMainWindow *mainWindow = new QMainWindow;
	Ui::ShareBoard ui;
	ui.setupUi(mainWindow);

	mainWindow->show();


	return app.exec();


}
