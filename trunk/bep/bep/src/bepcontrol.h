#ifndef BEPCONTROL_H
#define BEPCONTROL_H

#include <QtGui>

#include "bep.h"
#include "data.h"
#include "getdata.h"
#include "setdata.h"
#include "knscontrol.h"
#include "akbcontrol.h"
#include "accontrol.h"
#include "loadcontrol.h"
#include "coolercontrol.h"
#include "log.h"
#include "statdata.h"
#include "conf.h"
#include "network.h"

class bepcontrol: public QWidget {
		Q_OBJECT

	public:
		bepcontrol(QWidget *parent = 0);
		~bepcontrol();

	protected:
		void closeEvent(QCloseEvent *);

	private slots:
		void showTab(QString);
		void lostConnection();

	private:
		QTabWidget *tabs;
		QLabel *label8;
		QLabel *label9;
		QLabel *label10;
		bep *bepW;
		DATA *dataValues;
		GETDATA *getDataValues;
		SETDATA *setDataValues;
		knscontrol *kns1W;
		knscontrol *kns2W;
		knscontrol *kns3W;
		knscontrol *kns4W;
		akbcontrol *akb1W;
		akbcontrol *akb2W;
		accontrol *acW;
		loadcontrol *loadW;
		coolercontrol *coolerW;
		log *logger;
		statdata *stats;
		conf *confW;
		network *networker;
		QTcpSocket *tcpSocket;
		QPushButton *estConnBtn;
};

#endif
