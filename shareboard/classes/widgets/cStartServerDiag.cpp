#include "cStartServerDiag.h"


cStartServerDiag::cStartServerDiag(QWidget *parent) : QDialog(parent), ssd(new Ui::StartNetworkDialog)
{
	ssd->setupUi(this);
	QPushButton *startNetworkButton = findChild<QPushButton *>("startNetworkButton");
	QObject::connect(startNetworkButton, SIGNAL(clicked()), this, SLOT(mHandleServerStartButton()));
}

void cStartServerDiag::mHandleServerStartButton()
{
   hide();
}