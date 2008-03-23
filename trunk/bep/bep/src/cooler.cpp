#include <QtGui>
#include "cooler.h"

cooler::cooler(QWidget *parent) : QWidget(parent) {
// 	alarm = false;
// 	state = true;
	off = true;
	title = trUtf8("Вентилятор");
	angle = 0;

	timer = new QTimer(this);
	timer->stop();

	connect(timer, SIGNAL(timeout()), this, SLOT(rotate()));

	setCursor(Qt::PointingHandCursor);

	setFixedSize(60, 60);
}

cooler::~cooler() {

}

void cooler::paintEvent(QPaintEvent *) {
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.setPen(Qt::gray);
	painter.setBrush(Qt::gray);
	QRectF rectangle(rect().x() + 1, rect().y() + 1, rect().width() - 2, rect().height() - 2);
	int startAngle = -angle * 16;
	int spanAngle = -60 * 16;
	painter.drawPie(rectangle, startAngle, spanAngle);
	painter.drawPie(rectangle, startAngle + 120*16, spanAngle);
	painter.drawPie(rectangle, startAngle + 120*16 + 120*16, spanAngle);
	painter.drawEllipse(rect().width() / 2 - 5, rect().height() / 2 - 5, 10, 10);
}

// void load::setAlarm(bool Alarm) {
// 	if (alarm != Alarm) {
// 		alarm = Alarm;
// 		repaint();
// 	}
// }


void cooler::setTitle(QString Title) {
	if (title != Title) {
		title = Title;
		repaint();
	}
}

void cooler::setOff(bool Off) {
	if (off != Off) {
		off = Off;
		repaint();
		if (!off) timer->start(200);
		else timer->stop();
	}
}

void cooler::mousePressEvent(QMouseEvent *) {
	emit(itemClicked(title));
}

void cooler::rotate() {
	angle += 5;
	repaint();
}
