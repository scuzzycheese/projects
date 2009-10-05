#include "ui_shareboard.h"
#include "pWidget.h"
#include <QtGui/QButtonGroup>

int main(int argc, char **argv)
{

	QApplication app(argc, argv);
	QMainWindow *mainWindow = new QMainWindow;
	Ui::ShareBoard ui;
	ui.setupUi(mainWindow);

	QtColorPicker *clrPkr = mainWindow->findChild<QtColorPicker *>("colourPicker");

	pWidget *drawArea = mainWindow->findChild<pWidget *>("drawArea");
	QPushButton *clearButton = mainWindow->findChild<QPushButton *>("clearButton");


  	QObject::connect(clearButton, SIGNAL(clicked()), drawArea, SLOT(clearImage()));
	QObject::connect(clrPkr, SIGNAL(colorChanged(const QColor &)), drawArea, SLOT(setPenColorSig(const QColor &)));


	mainWindow->show();


	return app.exec();


}
