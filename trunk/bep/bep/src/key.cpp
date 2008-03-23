#include <QtGui>
#include "key.h"

key::key(QWidget *parent) : QWidget(parent) {
	state = false;
	title = trUtf8("Q1");
	frame = new QFrame();

	QHBoxLayout *mainLayout = new QHBoxLayout;
	mainLayout->addWidget(frame);
	setLayout(mainLayout);

	setFixedSize(42, 42);
}

key::~key() {

}

void key::paintEvent(QPaintEvent *) {
	QPainter painter(this);
	QPen pen = QPen(Qt::black);
	pen.setWidth(2);
	painter.setPen(pen);
	painter.setBrush(Qt::darkGreen);
	painter.setRenderHint(QPainter::Antialiasing);
	if (!state) {
		painter.drawLine(rect().x() + rect().width() / 2, rect().y(),
		                 rect().x() + rect().width() / 2, rect().y() + rect().height() / 2 - 10);

		painter.drawLine(rect().x() + rect().width() / 2, rect().y() + rect().height() / 2 + 9,
		                 rect().x() + rect().width() / 2 + 10, rect().y() + rect().height() / 2 - 10);

		painter.drawLine(rect().x() + rect().width() / 2, rect().y() + rect().height() / 2 + 10,
		                 rect().x() + rect().width() / 2, rect().y() + rect().height());

	} else {
		painter.drawLine(rect().x() + rect().width() / 2, rect().y(), rect().x() + rect().width() / 2, rect().y() + rect().height());
	}
	painter.setFont(QFont("Arial", 10));
	painter.drawText(rect(), Qt::AlignTop, title);
}

void key::setState(bool State) {
	if (state != State) {
		state = State;
		repaint();
	}
}

void key::setTitle(QString Title) {
	if (title != Title) {
		title = Title;
		repaint();
	}
}
