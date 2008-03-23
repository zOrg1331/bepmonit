#ifndef BEP_H
#define BEP_H

#include <QtGui>

#include "kns.h"
#include "akb.h"
#include "empty.h"
#include "key.h"
#include "load.h"
#include "acpower.h"
#include "ldefense.h"
#include "ilabel.h"
#include "cooler.h"
#include "data.h"
#include "knscontrol.h"
#include "akbcontrol.h"
#include "accontrol.h"
#include "loadcontrol.h"
#include "coolercontrol.h"
#include "log.h"
#include "conf.h"
#include "setdata.h"
#include "arrow.h"

class bep: public QWidget {
		Q_OBJECT

	public:
		bep(DATA *, knscontrol *, knscontrol *, knscontrol *, knscontrol *, akbcontrol *, akbcontrol *, accontrol *, loadcontrol *, coolercontrol *, log *, conf *, SETDATA *, QWidget *parent = 0);
		~bep();

	protected:
		void paintEvent(QPaintEvent*);
		void resizeEvent(QResizeEvent*);

	private slots:
		void updateData();
		void newMsg(int, const char *, int);

	signals:
		void itemClicked(QString);

	private:
		void placeWidgets();

		bool AKB1charging;
		bool AKB2charging;
		bool AKB1discharging;
		bool AKB2discharging;

		kns *knsW1;
		kns *knsW2;
		kns *knsW3;
		kns *knsW4;
		akb *akbW1;
		akb *akbW2;
		//	empty *empty1;
		key *key1;
		key *key2;
		key *key3;
		key *key4;
		key *key5;
		key *key6;
		key *key7;
		key *key8;
		load *load1;
		load *load2;
		load *load3;
		acpower *acpowerW;
		ldefense *ldefenseW;
		ilabel *ilabel1;
// 		ilabel *ilabel2;
		ilabel *ilabel3;
// 		ilabel *ilabel4;
		cooler *coolerW;
		DATA *dataValues;
		QTimer *timerData;
		knscontrol *kns1ctrl;
		knscontrol *kns2ctrl;
		knscontrol *kns3ctrl;
		knscontrol *kns4ctrl;
		akbcontrol *akb1ctrl;
		akbcontrol *akb2ctrl;
		accontrol *acctrl;
		loadcontrol *loadctrl;
		coolercontrol *coolerctrl;
		log *logger;
		conf *confData;
		SETDATA *setDataValues;
		QTableWidget *logW;

		int LDEFX, LDEFCX, LDEFY, LDEFCY, ACCX,	ACY, ACCY, ACH,	KNS1Y, KNS1CX, KNS1H, KNS2CX;
		int KNS2Y, KNS2H, KNS3CX, KNS3Y, KNS3H, KNS4CX,	KNS4Y, KNS4H, KEY1Y, KEY1CX, KEY2CX;
		int KEY2Y, KEY2H, KEY3CX, KEY3Y, KEY4CX, KEY4Y, KEY5CX, KEY5Y, KEY6CX, KEY6Y, KEY7CX;
		int KEY7Y, KEY8CX, KEY8Y, KEY3H, KEY1H, AKB2Y, AKB1Y;

		QPainterPath rightChargArrow;
		QPainterPath rightDischargArrow;
		QPainterPath leftChargArrow;
		QPainterPath leftDischargArrow;

		arrow *arrowRightCharg;
		arrow *arrowRightDischarg;
		arrow *arrowLeftCharg;
		arrow *arrowLeftDischarg;
};

#endif
