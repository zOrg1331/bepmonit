#ifndef LDEFENSE_H
#define LDEFENSE_H

#include <QtGui>
#include "mybasewidgets.h"

class ldefense: public QWidget {
		Q_OBJECT

	public:
		ldefense(QWidget *parent = 0);
		~ldefense();

	protected:
		void paintEvent(QPaintEvent*);

	signals:

	public slots:
		void setTitle(QString);
		void setState(bool);
		void setOff(bool);

	private slots:

	private:
		bool state;
		bool off;

		MyFrame *frame;
		MyLabel *label;
		QString title;

};

#endif
