#include "ui_shareboard.h"
#include "ui_connectDialog.h"
#include "cVectorDrawWidget.h"
#include <QtGui/QButtonGroup>
#include <QObject>
#include <QApplication>
#include "cServer.h"
#include "cConnDiag.h"
#include "cStartServerDiag.h"
#include "cClient.h"
#include "qtcolorpicker.h"
#include "cEngine.h"

//global evilness
cEngine *engine = new cEngine();

int main(int argc, char **argv)
{

	QApplication app(argc, argv);
	QMainWindow *mainWindow = new QMainWindow;
	Ui::ShareBoard ui;
	ui.setupUi(mainWindow);

	cConnDiag *connectDialog = new cConnDiag;
	cStartServerDiag *startServerDialog = new cStartServerDiag;


	QtColorPicker *clrPkr = mainWindow->findChild<QtColorPicker *>("colourPicker");
	QSlider *sldr = mainWindow->findChild<QSlider *>("penThickness");
	cVectorDrawWidget *drawArea = mainWindow->findChild<cVectorDrawWidget *>("drawArea");
	QPushButton *clearButton = mainWindow->findChild<QPushButton *>("clearButton");
	QPushButton *resetButton = mainWindow->findChild<QPushButton *>("resetButton");
	QDial *angleDial = mainWindow->findChild<QDial *>("orientation");
	QSlider *scale = mainWindow->findChild<QSlider *>("scale");
	QSpinBox *angleSpinBox = mainWindow->findChild<QSpinBox *>("angleSpinBox");

	QAction *connectToNetworkAction = mainWindow->findChild<QAction *>("actionConnect_to_Network");
	QAction *startServerAction = mainWindow->findChild<QAction *>("actionStart_Server_2");

	cMatrixWidget *worldMatrixWidget = mainWindow->findChild<cMatrixWidget *>("WM_W");
	cMatrixWidget *rotationMatrixWidget = mainWindow->findChild<cMatrixWidget *>("RM_W");
	cMatrixWidget *translationMatrixWidget = mainWindow->findChild<cMatrixWidget *>("TM_W");
	cMatrixWidget *scaleMatrixWidget = mainWindow->findChild<cMatrixWidget *>("SM_W");

	worldMatrixWidget->setTitle("dWorldMatrix");
	worldMatrixWidget->mSetMatrix(&(engine->dWorldMatrix));
	rotationMatrixWidget->setTitle("dRotationMatrix");
	rotationMatrixWidget->mSetMatrix(&(engine->dRotationMatrix));
	translationMatrixWidget->setTitle("dTranslationMatrix");
	translationMatrixWidget->mSetMatrix(&(engine->dTranslationMatrix));
	scaleMatrixWidget->setTitle("dScaleMatrix");
	scaleMatrixWidget->mSetMatrix(&(engine->dScaleMatrix));

	

	QObject::connect(connectToNetworkAction, SIGNAL(triggered()), connectDialog, SLOT(show()));
	QObject::connect(startServerAction, SIGNAL(triggered()), startServerDialog, SLOT(show()));


  	QObject::connect(clearButton, SIGNAL(clicked()), drawArea, SLOT(clearImage()));
  	QObject::connect(resetButton, SIGNAL(clicked()), drawArea, SLOT(mResetMatrices()));
	QObject::connect(clrPkr, SIGNAL(colorChanged(const QColor &)), drawArea, SLOT(setPenColorSlot(const QColor &)));
	QObject::connect(sldr, SIGNAL(valueChanged(int)), drawArea, SLOT(setPenWidthSlot(int)));
	QObject::connect(angleDial, SIGNAL(valueChanged(int)), drawArea, SLOT(rotateSlot(int)));
	QObject::connect(scale, SIGNAL(valueChanged(int)), drawArea, SLOT(scaleSlot(int)));
	QObject::connect(angleSpinBox, SIGNAL(valueChanged(int)), angleDial, SLOT(setValue(int)));
	QObject::connect(angleDial, SIGNAL(valueChanged(int)), angleSpinBox, SLOT(setValue(int)));

	QObject::connect(drawArea, SIGNAL(mMatrixChanged()), worldMatrixWidget, SLOT(mUpdate()));
	QObject::connect(drawArea, SIGNAL(mMatrixChanged()), rotationMatrixWidget, SLOT(mUpdate()));
	QObject::connect(drawArea, SIGNAL(mMatrixChanged()), translationMatrixWidget, SLOT(mUpdate()));
	QObject::connect(drawArea, SIGNAL(mMatrixChanged()), scaleMatrixWidget, SLOT(mUpdate()));


	/*
	clrPkr->insertColor(Qt::black, "Black", 1);
	clrPkr->insertColor(Qt::blue, "Blue", 2);
	clrPkr->insertColor(Qt::green, "Green", 3);
	clrPkr->insertColor(Qt::red, "Red", 4);
	clrPkr->insertColor(Qt::yellow, "Yellow", 5);
	clrPkr->insertColor(Qt::white, "White", 6);
	 */
	clrPkr->setStandardColors();


	cServer *serv = NULL;
	startServerDialog->mSetServer(serv);

	cClient *cli = new cClient();
	QObject::connect(connectDialog, SIGNAL(connectToHost(const QString &, quint16)), cli, SLOT(mConnectToHostSlot(const QString &, quint16)));


	
	mainWindow->show();


	return app.exec();


}
