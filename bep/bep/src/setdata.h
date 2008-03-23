#ifndef SETDATA_H
#define SETDATA_H

#include <QtCore>
#include <QtNetwork>
#include "data.h"

class SETDATA : public QObject {
		Q_OBJECT

	public:
		SETDATA(DATA *dataValues, QTcpSocket *);

	public slots:
		void writeDataF();
		void writeData();

	private:
		DATA *dataValues;
		QTcpSocket *tcpSocket;

};

#endif
