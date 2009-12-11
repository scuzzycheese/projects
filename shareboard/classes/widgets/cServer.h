#ifndef CSERVER_H
#define CSERVER_H


#define SERVERPORT 1234
#define SERVERBIND QHostAddress::Any


#include <Qt/QtNetwork>
#include <QWidget>

class cServer : public QWidget
{
	Q_OBJECT

	private:
		QTcpServer *dTcpSrv;

	public:
		cServer(QWidget *parent = 0);

	public slots:
		void mAcceptConnection();


};


#endif
