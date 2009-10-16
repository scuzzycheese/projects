#include "ui_shareboard.h"
#include "cVectorDrawWidget.h"
#include <QtGui/QButtonGroup>
#include <QObject>

int main(int argc, char **argv)
{

	QApplication app(argc, argv);
	QMainWindow *mainWindow = new QMainWindow;
	Ui::ShareBoard ui;
	ui.setupUi(mainWindow);

	QtColorPicker *clrPkr = mainWindow->findChild<QtColorPicker *>("colourPicker");
	QSlider *sldr = mainWindow->findChild<QSlider *>("penThickness");
	cVectorDrawWidget *drawArea = mainWindow->findChild<cVectorDrawWidget *>("drawArea");
	QPushButton *clearButton = mainWindow->findChild<QPushButton *>("clearButton");
	QDial *angleDial = mainWindow->findChild<QDial *>("orientation");
	QSlider *scale = mainWindow->findChild<QSlider *>("scale");

	cMatrixWidget *worldMatrixWidget = mainWindow->findChild<cMatrixWidget *>("WM_W");
	cMatrixWidget *rotationMatrixWidget = mainWindow->findChild<cMatrixWidget *>("RM_W");
	cMatrixWidget *translationMatrixWidget = mainWindow->findChild<cMatrixWidget *>("TM_W");
	cMatrixWidget *scaleMatrixWidget = mainWindow->findChild<cMatrixWidget *>("SM_W");

	worldMatrixWidget->setTitle("dWorldMatrix");
	worldMatrixWidget->mSetMatrix(drawArea->mGetWorldMatrix());
	rotationMatrixWidget->setTitle("dRotationMatrix");
	rotationMatrixWidget->mSetMatrix(drawArea->mGetRotationMatrix());
	translationMatrixWidget->setTitle("dTranslationMatrix");
	translationMatrixWidget->mSetMatrix(drawArea->mGetTranslationMatrix());
	scaleMatrixWidget->setTitle("dScaleMatrix");
	scaleMatrixWidget->mSetMatrix(drawArea->mGetScaleMatrix());

	


  	QObject::connect(clearButton, SIGNAL(clicked()), drawArea, SLOT(clearImage()));
	QObject::connect(clrPkr, SIGNAL(colorChanged(const QColor &)), drawArea, SLOT(setPenColorSlot(const QColor &)));
	QObject::connect(sldr, SIGNAL(valueChanged(int)), drawArea, SLOT(setPenWidthSlot(int)));
	QObject::connect(angleDial, SIGNAL(valueChanged(int)), drawArea, SLOT(rotateSlot(int)));
	QObject::connect(scale, SIGNAL(valueChanged(int)), drawArea, SLOT(scaleSlot(int)));

	QObject::connect(drawArea, SIGNAL(mMatrixChanged()), worldMatrixWidget, SLOT(mUpdate()));
	QObject::connect(drawArea, SIGNAL(mMatrixChanged()), rotationMatrixWidget, SLOT(mUpdate()));
	QObject::connect(drawArea, SIGNAL(mMatrixChanged()), translationMatrixWidget, SLOT(mUpdate()));
	QObject::connect(drawArea, SIGNAL(mMatrixChanged()), scaleMatrixWidget, SLOT(mUpdate()));


	clrPkr->insertColor(Qt::black, "Black", 1);
	clrPkr->insertColor(Qt::blue, "Blue", 2);
	clrPkr->insertColor(Qt::green, "Green", 3);
	clrPkr->insertColor(Qt::red, "Red", 4);
	clrPkr->insertColor(Qt::yellow, "Yellow", 5);
	clrPkr->insertColor(Qt::white, "White", 6);

	mainWindow->show();


	return app.exec();


}
