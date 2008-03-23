#include <QtGui>
#include "empty.h"

empty::empty(QWidget *parent) : QWidget(parent) {
	gBox = new QGroupBox(this);
	label = new QLabel(trUtf8("Отключен"));

	QVBoxLayout *gBoxLayout = new QVBoxLayout;
	gBoxLayout->addWidget(label, 0, Qt::AlignHCenter);
	gBoxLayout->setSpacing(1);
	gBoxLayout->setMargin(1);
	gBox->setLayout(gBoxLayout);

	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(gBox);
	mainLayout->setSpacing(1);
	mainLayout->setMargin(1);

	setLayout(mainLayout);

	setCursor(Qt::PointingHandCursor);
}

empty::~empty() {

}

void empty::mousePressEvent(QMouseEvent *) {
	emit(itemClicked(title));
}

void empty::setTitle(QString Title) {
	title = Title;
}
