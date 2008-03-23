#ifndef GETDATA_H
#define GETDATA_H

#include <QtCore>
#include <QtNetwork>
#include "data.h"

#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>

class GETDATA : public QObject {
		Q_OBJECT

	public:
		GETDATA(DATA *, QTcpSocket *);

	public slots:
		void setSNMPSess(netsnmp_session *);

	private slots:
		void readDataF();
		void readDataN();

	private:
		DATA *dataValues;
		netsnmp_session *ss;

		QTimer *timer;
		quint64 blockSize;

		QTcpSocket *tcpSocket;
};

#endif
