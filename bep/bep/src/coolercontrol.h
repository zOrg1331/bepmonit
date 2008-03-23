#ifndef COOLERCONTROL_H
#define COOLERCONTROL_H

#include <QtGui>
#include "data.h"
#include "setdata.h"
#include "cooler.h"

class coolercontrol: public QWidget {
		Q_OBJECT

	public:
		coolercontrol(DATA *, SETDATA *, QWidget *parent = 0);
		~coolercontrol();

		void setOff(bool);

	public slots:

	private slots:
		void switchCooler();

	private:
		DATA *dataValues;
		SETDATA *setDataValues;

		cooler *coolerW;
		QLabel *statusLabel2;
		QPushButton *switchButton;

};

#endif
