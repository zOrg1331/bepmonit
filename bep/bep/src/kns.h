#ifndef KNS_H
#define KNS_H

#include <QtGui>
#include "mybasewidgets.h"

class kns: public QWidget {
		Q_OBJECT

	public:
		kns(QWidget *parent = 0);
		~kns();

	protected:
		void paintEvent(QPaintEvent*);
		void mousePressEvent(QMouseEvent*);

	signals:
		void itemClicked(QString);

	public slots:
		void setTitle(QString);
		void setTemp(double);
// 		void setNorma(bool);
		void setAvar(bool);
		void setAvarseti(bool);
		void setOgran(bool);
		void setPeregrev(bool);
		void setOff(bool);

	private slots:

	private:
		bool off;
		bool norm;
		bool avar;
		bool avarseti;
		bool ogran;
		bool peregrev;
		QString title;

		MyLCDNumber *tempLCD;

};

#endif
