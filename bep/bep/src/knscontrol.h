#ifndef KNSCONTROL_H
#define KNSCONTROL_H

#include <QtGui>
#include "kns.h"
#include "data.h"
#include "zchart.h"
#include "statdata.h"
#include "setdata.h"

class knscontrol: public QWidget {
		Q_OBJECT

	public:
		knscontrol(int, DATA *, statdata *, SETDATA *, QWidget *parent = 0);
		~knscontrol();

		void setOff(bool);
// 		void setNorma(bool);
		void setAvar(bool);
		void setAvarseti(bool);
		void setOgran(bool);
		void setPeregrev(bool);
		void setTemp(float);

	public slots:

	private slots:
		void switchKNS();
		void updateGraphs();

	private:
		bool off;
		QString oldstatus;

		DATA *dataValues;
		int KnsNum;
		SETDATA *setDataValues;

		kns *knsW;
		QLabel *tempLabel2;
		QLabel *statusLabel2;
		QPushButton *switchButton;

		ZChart *chartTemp;

		ZSimpleSeries *tempGraph;

		statdata *stats;

		QVector<float> *tempData;
		QVector<QTime> *tempTime;

};

#endif
