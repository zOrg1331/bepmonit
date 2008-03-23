#ifndef ILABEL_H
#define ILABEL_H

#include <QtGui>
#include "mybasewidgets.h"

class ilabel: public QWidget {
		Q_OBJECT

	public:
		ilabel(QWidget *parent = 0);
		~ilabel();

		QString getTitle();

	protected:

	signals:

	public slots:
		void setTitle(QString);

	private slots:

	private:
		QString title;

		MyFrame *frame;
		MyLabel *label;

};

#endif
