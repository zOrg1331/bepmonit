#ifndef GETDATA_H
#define GETDATA_H

#include <QtCore>
#include <QtNetwork>
#include "data.h"

class GETDATA : public QObject {
	Q_OBJECT

	public:
		GETDATA(DATA *);

	public slots:
		void readData();
		void setSocket(QTcpSocket *);

	private:
		DATA *dataValues;
		QTcpSocket *tcpSocket;
		quint64 blockSize;
};

#endif
