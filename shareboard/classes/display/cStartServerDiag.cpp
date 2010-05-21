#include "cStartServerDiag.h"
#include <QMessageBox>


cStartServerDiag::cStartServerDiag(QWidget *parent) : QDialog(parent), ssd(new Ui::StartNetworkDialog), server(NULL)
{
	ssd->setupUi(this);
	QPushButton *startNetworkButton = findChild<QPushButton *>("startNetworkButton");
	QObject::connect(startNetworkButton, SIGNAL(clicked()), this, SLOT(mHandleServerStartButton()));
}

void cStartServerDiag::mHandleServerStartButton()
{
	QLineEdit *networkName = findChild<QLineEdit *>("networkName");
	if(!server)
	{
		server = new cServer(networkName->text());
	}
	else
	{
		QMessageBox msgBox;
		msgBox.setText("The server is already running!");
		msgBox.exec();
	}
   hide();
}

void cStartServerDiag::mSetServer(cServer *srv)
{
	server = srv;
}