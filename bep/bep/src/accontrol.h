#ifndef ACCONTROL_H
#define ACCONTROL_H

#include <QtGui>
#include "acpower.h"
#include "data.h"
#include "zchart.h"
#include "statdata.h"
#include "setdata.h"

class accontrol: public QWidget {
		Q_OBJECT

	public:
		accontrol(DATA *, statdata *, SETDATA *, QWidget *parent = 0);
		~accontrol();

// 		void setOff(bool);
		void setU(float);
// 		void setHz(float);

	public slots:

	private slots:
// 		void switchAC();
		void updateGraphs();

	private:
		DATA *dataValues;
		SETDATA *setDataValues;

		acpower *acpowerW;
// 		QLabel *statusLabel2;
		QLabel *uLabel2;
// 		QLabel *hzLabel2;
// 		QPushButton *switchButton;

		ZChart *chartU;
// 		ZChart *chartHz;

		ZSimpleSeries *uGraph;
// 		ZSimpleSeries *hzGraph;

		statdata *stats;

		QVector<float> *uData;
// 		QVector<float> *hzData;
		QVector<QTime> *uTime;
// 		QVector<QTime> *hzTime;

};

#endif
