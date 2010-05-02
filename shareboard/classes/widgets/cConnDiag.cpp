#include "cConnDiag.h"


cConnDiag::cConnDiag(QWidget *parent) : QDialog(parent), cd(new Ui::ConnectDialog) 
{
	cd->setupUi(this);
	QPushButton *connectButton = findChild<QPushButton *>("connectButton");
	QObject::connect(connectButton, SIGNAL(clicked()), this, SLOT(mHandleConnectButton()));

}


void cConnDiag::mHandleConnectButton()
{
	QLineEdit *hostLine = findChild<QLineEdit *>("host");
	emit(connectToHost(hostLine->text(), SERVERPORT));

   hide();
}