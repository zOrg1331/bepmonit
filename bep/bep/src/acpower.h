#ifndef ACPOWER_H
#define ACPOWER_H

#include <QtGui>

class acpower: public QWidget {
		Q_OBJECT

	public:
		acpower(QWidget *parent = 0);
		~acpower();

	protected:
		void paintEvent(QPaintEvent*);
		void mousePressEvent(QMouseEvent*);

	signals:
		void itemClicked(QString);

	public slots:
		void setTitle(QString);
		void setOff(bool);
// 		void setU(float);
// 		void setHz(float);

	private slots:

	private:
		QString title;
		bool off;

};

#endif
