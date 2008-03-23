#ifndef ARROW_H
#define ARROW_H

#include <QtGui>

class arrow: public QWidget {
	Q_OBJECT

	public:
		arrow(QWidget *parent = 0);
		~arrow();

	protected:
		void paintEvent(QPaintEvent*);

	public slots:
		void setPath(QPainterPath);
		void setInvisible(bool);

	private slots:

	private:
		QPainterPath path;
		bool invisible;

};

#endif
