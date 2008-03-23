#include <QtGui>
#include "load.h"

load::load(QWidget *parent) : QWidget(parent) {
// 	alarm = false;
	state = true;
	off = false;
	title = trUtf8("Нагрузка");

	setCursor(Qt::PointingHandCursor);

	setFixedSize(100, 170);
}

load::~load() {

}

void load::paintEvent(QPaintEvent *) {
	QPainter painter(this);
	painter.setPen(Qt::black);
	if (!state) {
		painter.setBrush(Qt::red);
	} else {
		painter.setBrush(Qt::darkGreen);
	}
	if (off) {
		painter.setBrush(Qt::gray);
	}
	painter.setFont(QFont("Arial", 14));
	painter.drawRect(rect().x(), rect().y(), rect().width() - 1, rect().height() - 1);
	painter.drawText(rect(), Qt::AlignCenter, title);
}

// void load::setAlarm(bool Alarm) {
// 	if (alarm != Alarm) {
// 		alarm = Alarm;
// 		repaint();
// 	}
// }

void load::setState(bool State) {
	if (state != State) {
		state = State;
		repaint();
	}
}

void load::setTitle(QString Title) {
	if (title != Title) {
		title = Title;
		repaint();
	}
}

void load::setOff(bool Off) {
	if (off != Off) {
		off = Off;
		repaint();
	}
}

void load::mousePressEvent(QMouseEvent *) {
	emit(itemClicked(title));
}
