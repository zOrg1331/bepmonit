#include <QtGui>
#include "mybasewidgets.h"

MyLabel::MyLabel() : QLabel() {

}

void MyLabel::mousePressEvent(QMouseEvent *event) {
	if (event->button() == Qt::LeftButton) {
		event->ignore();
	} else {
		QLabel::mousePressEvent(event);
	}
}

MyFrame::MyFrame() : QFrame() {

}

void MyFrame::mousePressEvent(QMouseEvent *event) {
	if (event->button() == Qt::LeftButton) {
		event->ignore();
	} else {
		QFrame::mousePressEvent(event);
	}
}

MyGBox::MyGBox() : QGroupBox() {

}

void MyGBox::mousePressEvent(QMouseEvent *event) {
	if (event->button() == Qt::LeftButton) {
		event->ignore();
	} else {
		QGroupBox::mousePressEvent(event);
	}
}

MyLCDNumber::MyLCDNumber() : QLCDNumber() {

}

void MyLCDNumber::mousePressEvent(QMouseEvent *event) {
	if (event->button() == Qt::LeftButton) {
		event->ignore();
	} else {
		QLCDNumber::mousePressEvent(event);
	}
}
