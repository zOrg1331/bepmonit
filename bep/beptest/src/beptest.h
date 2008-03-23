#ifndef BEPTEST_H
#define BEPTEST_H

#include <QtGui>

#include "data.h"
#include "getdata.h"
#include "setdata.h"

class beptest: public QWidget {
	Q_OBJECT

	public:
		beptest(QWidget *parent = 0);
		~beptest();

	protected:

	private slots:
		void setWidgetsState();
		void updateData();
		void estConn();
		void readData();

	private:
		DATA *data;
		GETDATA *getdata;
		SETDATA *setdata;

		QTcpServer *tcpServer;

		QPushButton *ldefState;
// 		QPushButton *ldefOff;
// 		QPushButton *ACOff;
		QLineEdit *ACU;
		QLabel *ACUl;
// 		QLineEdit *ACHz;
// 		QLabel *ACHzl;
		QPushButton *KNS1Off;
// 		QPushButton *KNS1Norma;
		QPushButton *KNS1Avar;
		QPushButton *KNS1Avarseti;
		QPushButton *KNS1Ogran;
		QPushButton *KNS1Peregrev;
		QLineEdit *KNS1Temp;
		QLabel *KNS1Templ;
		QPushButton *KNS2Off;
// 		QPushButton *KNS2Norma;
		QPushButton *KNS2Avar;
		QPushButton *KNS2Avarseti;
		QPushButton *KNS2Ogran;
		QPushButton *KNS2Peregrev;
		QLineEdit *KNS2Temp;
		QLabel *KNS2Templ;
		QPushButton *KNS3Off;
// 		QPushButton *KNS3Norma;
		QPushButton *KNS3Avar;
		QPushButton *KNS3Avarseti;
		QPushButton *KNS3Ogran;
		QPushButton *KNS3Peregrev;
		QLineEdit *KNS3Temp;
		QLabel *KNS3Templ;
		QPushButton *KNS4Off;
// 		QPushButton *KNS4Norma;
		QPushButton *KNS4Avar;
		QPushButton *KNS4Avarseti;
		QPushButton *KNS4Ogran;
		QPushButton *KNS4Peregrev;
		QLineEdit *KNS4Temp;
		QLabel *KNS4Templ;
		QPushButton *AKB1Off;
// 		QPushButton *AKB1Charging;
// 		QPushButton *AKB1Discharging;
// 		QPushButton *AKB1Fulldischarg;
// 		QPushButton *AKB1Trening;
		QLineEdit *AKB1U1;
		QLineEdit *AKB1U2;
		QLineEdit *AKB1U3;
		QLineEdit *AKB1U4;
		QLineEdit *AKB1U5;
		QLineEdit *AKB1I;
		QLineEdit *AKB1Temp;
		QLabel *AKB1U1l;
		QLabel *AKB1U2l;
		QLabel *AKB1U3l;
		QLabel *AKB1U4l;
		QLabel *AKB1U5l;
		QLabel *AKB1Il;
		QLabel *AKB1Templ;
		QPushButton *AKB2Off;
// 		QPushButton *AKB2Charging;
// 		QPushButton *AKB2Discharging;
// 		QPushButton *AKB2Fulldischarg;
// 		QPushButton *AKB2Trening;
		QLineEdit *AKB2U1;
		QLineEdit *AKB2U2;
		QLineEdit *AKB2U3;
		QLineEdit *AKB2U4;
		QLineEdit *AKB2U5;
		QLineEdit *AKB2I;
		QLineEdit *AKB2Temp;
		QLabel *AKB2U1l;
		QLabel *AKB2U2l;
		QLabel *AKB2U3l;
		QLabel *AKB2U4l;
		QLabel *AKB2U5l;
		QLabel *AKB2Il;
		QLabel *AKB2Templ;
		QPushButton *LoadOff;
		QLineEdit *LoadI;
		QLabel *LoadIl;
		QPushButton *Load1State;
		QPushButton *Load2State;
		QPushButton *Load3State;
		QPushButton *CoolerOff;
		QPushButton *CoolerForcedOn;
		QLineEdit *ExitU;
		QLabel *ExitUl;
};

#endif
