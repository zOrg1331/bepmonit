#include <QtGui>
#include "acpower.h"

acpower::acpower(QWidget *parent) : QWidget(parent) {
	title = QString(trUtf8("Питание"));
	off = false;

	setCursor(Qt::PointingHandCursor);

	setFixedSize(42, 42);
}

acpower::~acpower() {

}

void acpower::paintEvent(QPaintEvent *) {
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	QPen pen = QPen(Qt::black);
	pen.setWidth(1);
	painter.setPen(pen);
	painter.drawArc(rect().x() + 11, rect().y() + 15, 10, 10, 16*0, 16*200);
	painter.drawArc(rect().x() + 21, rect().y() + 17, 10, 10, 16*0, -16*200);
	pen.setWidth(2);
	painter.setPen(pen);
	painter.setBrush(Qt::NoBrush);
	painter.drawEllipse(rect().x() + 1, rect().y() + 1, 40, 40);
	if (off) {
		painter.setPen(Qt::gray);
		painter.setBrush(Qt::Dense6Pattern);
		painter.drawEllipse(rect().x() + 1, rect().y() + 1, 40, 40);
	}
}

void acpower::mousePressEvent(QMouseEvent *) {
	emit(itemClicked(title));
}

void acpower::setTitle(QString Title) {
	if (title != Title) {
		title = Title;
	}
}

void acpower::setOff(bool Off) {
	if (off != Off) {
		off = Off;
		repaint();
	}
}

// void acpower::setU(float N) {
//
// }
//
// void acpower::setHz(float N) {
//
// }
