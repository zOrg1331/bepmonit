#ifndef LOADCONTROL_H
#define LOADCONTROL_H

#include <QtGui>
#include "data.h"
#include "zchart.h"
#include "statdata.h"
#include "setdata.h"

class loadcontrol: public QWidget {
		Q_OBJECT

	public:
		loadcontrol(DATA *, statdata *, SETDATA *, QWidget *parent = 0);
		~loadcontrol();

		void setExitU(float);
		void setI(float);
		void setOff(bool);
		void setState1(bool);
		void setState2(bool);
		void setState3(bool);

	public slots:

	private slots:
		void switchLoad();
		void updateGraphs();

	private:
		DATA *dataValues;
		SETDATA *setDataValues;

// 		acpower *acpowerW;
		QLabel *statusLabel2;
		QLabel *uLabel2;
		QLabel *iLabel2;
		QLabel *avarLabel12;
		QLabel *avarLabel22;
		QLabel *avarLabel32;
// 		QLabel *hzLabel2;
		QPushButton *switchButton;

		ZChart *chartU;
		ZChart *chartI;
// 		ZChart *chartHz;

		ZSimpleSeries *uGraph;
		ZSimpleSeries *iGraph;
// 		ZSimpleSeries *hzGraph;

		statdata *stats;

		QVector<float> *uData;
		QVector<float> *iData;
		QVector<QTime> *uTime;
		QVector<QTime> *iTime;

};

#endif
