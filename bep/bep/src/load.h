#ifndef LOAD_H
#define LOAD_H

#include <QtGui>

class load: public QWidget {
		Q_OBJECT

	public:
		load(QWidget *parent = 0);
		~load();

	protected:
		void paintEvent(QPaintEvent*);
		void mousePressEvent(QMouseEvent*);

	signals:
		void itemClicked(QString);

	public slots:
		void setTitle(QString);
// 		void setAlarm(bool);
		void setState(bool);
		void setOff(bool);

	private slots:

	private:
// 		bool alarm;
		bool state;
		bool off;
		QString title;

};

#endif
