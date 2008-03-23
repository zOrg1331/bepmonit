#ifndef COOLER_H
#define COOLER_H

#include <QtGui>

class cooler: public QWidget {
		Q_OBJECT

	public:
		cooler(QWidget *parent = 0);
		~cooler();

	protected:
		void paintEvent(QPaintEvent*);
		void mousePressEvent(QMouseEvent*);

	signals:
		void itemClicked(QString);

	public slots:
		void setTitle(QString);
// 		void setAlarm(bool);
// 		void setState(bool);
		void setOff(bool);

	private slots:
		void rotate();

	private:
// 		bool alarm;
// 		bool state;
		bool off;
		QString title;
		QTimer *timer;
		int angle;

};

#endif
