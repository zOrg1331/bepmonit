#ifndef SETDATA_H
#define SETDATA_H

#include <QtCore>
#include <QtNetwork>
#include "data.h"

class SETDATA : public QObject {
	Q_OBJECT

	public:
		SETDATA(DATA *dataValues);

	public slots:
		void writeData();
		void writeDataF();
		void setSocket(QTcpSocket *);

	private:
		DATA *dataValues;
		QTcpSocket *tcpSocket;

};

#endif
