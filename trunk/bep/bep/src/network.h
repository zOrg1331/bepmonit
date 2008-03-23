#ifndef NETWORK_H
#define NETWORK_H

#include <QtCore>
#include <QtNetwork>
#include "log.h"
#include "conf.h"
#include "getdata.h"

#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>

class network: public QObject {
	Q_OBJECT

	public:
		network(QTcpSocket *, log *, conf *, GETDATA *);
		~network();

	protected:

	public slots:
		void estConnection();

	private slots:
		void connectionEst();

	private:
		log *logger;
		conf *confer;
		QTcpSocket *tcpSocket;
		GETDATA *getData;
};

#endif
