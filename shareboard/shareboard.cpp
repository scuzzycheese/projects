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
	QSlider *sldr = mainWindow->findChild<QSlider *>("penThickness");
	pWidget *drawArea = mainWindow->findChild<pWidget *>("drawArea");
	QPushButton *clearButton = mainWindow->findChild<QPushButton *>("clearButton");
	QLabel *widthVal = mainWindow->findChild<QLabel *>("widthVal");


  	QObject::connect(clearButton, SIGNAL(clicked()), drawArea, SLOT(clearImage()));
	QObject::connect(clrPkr, SIGNAL(colorChanged(const QColor &)), drawArea, SLOT(setPenColorSlot(const QColor &)));
	QObject::connect(sldr, SIGNAL(valueChanged(int)), drawArea, SLOT(setPenWidthSlot(int)));
	QObject::connect(sldr, SIGNAL(valueChanged(int)), widthVal, SLOT(setNum(int)));


	clrPkr->insertColor(Qt::black, "Black", 1);
	clrPkr->insertColor(Qt::blue, "Blue", 2);
	clrPkr->insertColor(Qt::green, "Green", 3);
	clrPkr->insertColor(Qt::red, "Red", 4);
	clrPkr->insertColor(Qt::yellow, "Yellow", 5);
	clrPkr->insertColor(Qt::white, "White", 6);

	mainWindow->show();


	return app.exec();


}
