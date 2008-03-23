#ifndef MYBASEWIDGETS_H
#define MYBASEWIDGETS_H

#include <QtGui>

class MyLabel : public QLabel {
	public:
		MyLabel();

	protected:
		void mousePressEvent(QMouseEvent *event);
};

class MyFrame : public QFrame {
	public:
		MyFrame();

	protected:
		void mousePressEvent(QMouseEvent *event);
};

class MyGBox : public QGroupBox {
	public:
		MyGBox();

	protected:
		void mousePressEvent(QMouseEvent *event);
};

class MyLCDNumber : public QLCDNumber {
	public:
		MyLCDNumber();

	protected:
		void mousePressEvent(QMouseEvent *event);
};

#endif
