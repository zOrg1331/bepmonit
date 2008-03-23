#ifndef AKBCONTROL_H
#define AKBCONTROL_H

#include <QtGui>
#include "akb.h"
#include "data.h"
#include "zchart.h"
#include "statdata.h"
#include "setdata.h"

class akbcontrol: public QWidget {
		Q_OBJECT

	public:
		akbcontrol(int, DATA *, statdata *, SETDATA *, QWidget *parent = 0);
		~akbcontrol();

		void setOff(bool);
		void setCharging(bool);
		void setDischarging(bool);
		void setFulldischarg(bool);
// 		void setTrening(bool);
		void setU1(float);
		void setU2(float);
		void setU3(float);
		void setU4(float);
		void setU5(float);
		void setI(float);
		void setTemp(float);

	public slots:

	private slots:
		void switchAKB();
// 		void switchAKBTren();
		void updateGraphs();

	private:
		bool off;
		DATA *dataValues;
		int AkbNum;
		SETDATA *setDataValues;

		akb *akbW;
		QPushButton *switchButton;
// 		QPushButton *switchTrenButton;
		QLabel *statusLabel2;
		QLabel *u1Label;
		QLabel *u2Label;
		QLabel *u3Label;
		QLabel *u4Label;
		QLabel *u5Label;
		QLabel *iLabel;
		QLabel *tempLabel;

		ZChart *chartU;
		ZChart *chartI;
		ZChart *chartTemp;

		ZSimpleSeries *u1Graph;
		ZSimpleSeries *u2Graph;
		ZSimpleSeries *u3Graph;
		ZSimpleSeries *u4Graph;
		ZSimpleSeries *u5Graph;
		ZSimpleSeries *iGraph;
		ZSimpleSeries *tempGraph;

		statdata *stats;

		QVector<float> *u1Data;
		QVector<float> *u2Data;
		QVector<float> *u3Data;
		QVector<float> *u4Data;
		QVector<float> *u5Data;
		QVector<float> *iData;
		QVector<float> *tempData;
		QVector<QTime> *u1Time;
		QVector<QTime> *u2Time;
		QVector<QTime> *u3Time;
		QVector<QTime> *u4Time;
		QVector<QTime> *u5Time;
		QVector<QTime> *iTime;
		QVector<QTime> *tempTime;
};

#endif
