#ifndef EMPTY_H
#define EMPTY_H

#include <QtGui>

class empty: public QWidget {
		Q_OBJECT

	public:
		empty(QWidget *parent = 0);
		~empty();

	protected:
		void mousePressEvent(QMouseEvent*);

	public slots:
		void setTitle(QString);

	signals:
		void itemClicked(QString);

	private slots:

	private:
		QString title;
		QGroupBox *gBox;
		QLabel *label;

};

#endif
