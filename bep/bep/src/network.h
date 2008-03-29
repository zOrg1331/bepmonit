#ifndef NETWORK_H
#define NETWORK_H

#include <QtCore>
#include <QtNetwork>
#include "log.h"
#include "conf.h"
#include "getdata.h"
#include "stunnel.h"

// #include <net-snmp/net-snmp-config.h>
// #include <net-snmp/net-snmp-includes.h>

class network: public QObject {
	Q_OBJECT

	public:
		network(QTcpSocket *, log *, conf *, GETDATA *);
		~network();

	protected:

	public slots:
		void estConnection();
		void closeConnection();

	private slots:
		void connectionEst();
		void connectToDevice();
		void reconnect();
		void displayError(QAbstractSocket::SocketError);

	private:
		log *logger;
		conf *confer;
		QTcpSocket *tcpSocket;
		GETDATA *getData;
		stunnel *stunn;
};

#endif
