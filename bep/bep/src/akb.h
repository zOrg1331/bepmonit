#ifndef AKB_H
#define AKB_H

#include <QtGui>
#include "mybasewidgets.h"

class akb: public QWidget {
		Q_OBJECT

	public:
		akb(QWidget *parent = 0);
		~akb();

	protected:
		void paintEvent(QPaintEvent*);
		void mousePressEvent(QMouseEvent*);

	signals:
		void itemClicked(QString);

	public slots:
		void setTitle(QString);
		void setTemp(double);
		void setU1(double);
		void setU2(double);
		void setU3(double);
		void setU4(double);
		void setU5(double);
		void setI(double);
		void setOff(bool);
		void setCharging(bool);
		void setDischarging(bool);
		void setFulldischarg(bool);
// 		void setTrening(bool);

	private slots:

	private:
		bool off;
		bool charging;
		bool discharging;
		bool fulldischarging;
// 		bool trening;
		QString title;
		QString status;
		QString oldstatus;

		/*		MyGBox *gBox;
				MyGBox *valuesBox;
				MyLabel *u1Label;
				MyLabel *u2Label;
				MyLabel *u3Label;
				MyLabel *u4Label;
				MyLabel *u5Label;*/
		MyLCDNumber *u1LCD;
		MyLCDNumber *u2LCD;
		MyLCDNumber *u3LCD;
		MyLCDNumber *u4LCD;
		MyLCDNumber *u5LCD;
// 		MyLabel *iLabel;
		MyLCDNumber *iLCD;
// 		MyLabel *tempLabel;
		MyLCDNumber *tempLCD;
// 		MyLabel *statusLabel;

};

#endif
