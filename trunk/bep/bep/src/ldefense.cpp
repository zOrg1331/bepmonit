#include <QtGui>
#include "ldefense.h"

ldefense::ldefense(QWidget *parent) : QWidget(parent) {
	title = trUtf8("Грозозащита");
	state = true;
	off = false;

	frame = new MyFrame();
	label = new MyLabel();

	label->setText(title);

	QHBoxLayout *frameLayout = new QHBoxLayout;
	frameLayout->addWidget(label, 0, Qt::AlignHCenter);
	frameLayout->setSpacing(0);
	frameLayout->setMargin(0);
	frame->setLayout(frameLayout);

	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(frame);
	mainLayout->setSpacing(0);
	mainLayout->setMargin(0);

	setLayout(mainLayout);

	setFixedSize(98, 25);
}

ldefense::~ldefense() {

}

void ldefense::setTitle(QString Title) {
	if (title != Title) {
		title = Title;
		label->setText(title);
	}
}

void ldefense::setState(bool State) {
	if (state != State) {
		state = State;
		repaint();
	}
}

void ldefense::setOff(bool Off) {
	if (off != Off) {
		off = Off;
		repaint();
	}
}

void ldefense::paintEvent(QPaintEvent *) {
	QPainter painter(this);
	if (state and !off) {
		painter.setBrush(Qt::NoBrush);
		painter.setPen(Qt::darkGreen);
	} else if (!state and !off) {
		painter.setBrush(Qt::red);
		painter.setPen(Qt::red);
		static const QPointF points[8] = {
			QPointF(rect().width() / 2 + 12, 2),
			QPointF(rect().width() / 2, rect().height() / 2 - 2),
			QPointF(rect().width() / 2 + 4, rect().height() / 2 - 2),
			QPointF(rect().width() / 2 - 12, rect().height() - 3),
			QPointF(rect().width() / 2 + 10, rect().height() / 2 - 4),
			QPointF(rect().width() / 2 + 6, rect().height() / 2 - 4),
			QPointF(rect().width() / 2 + 16, 2),
			QPointF(rect().width() / 2 + 12, 2)
		};
		painter.drawPolygon(points, 8);
		painter.setBrush(Qt::NoBrush);
	}
	if (off) {
		painter.setPen(Qt::gray);
		painter.setBrush(Qt::Dense6Pattern);
	}
	painter.drawRect(rect().x(), rect().y(), rect().width() - 1, rect().height() - 1);
}
