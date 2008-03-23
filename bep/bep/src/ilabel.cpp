#include <QtGui>
#include "ilabel.h"

ilabel::ilabel(QWidget *parent) : QWidget(parent) {
	frame = new MyFrame();
	label = new MyLabel();

	frame->setFrameStyle(QFrame::Panel | QFrame::Sunken);
	label->setText(trUtf8("В, Гц"));

	QVBoxLayout *frameLayout = new QVBoxLayout;
	frameLayout->addWidget(label);
	frameLayout->setSpacing(1);
	frameLayout->setMargin(1);
	frame->setLayout(frameLayout);

	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(frame);
	mainLayout->setSpacing(1);
	mainLayout->setMargin(1);

	setLayout(mainLayout);
}

ilabel::~ilabel() {

}

void ilabel::setTitle(QString Title) {
	if (title != Title) {
		title = Title;
		label->setText(title);
	}
}

QString ilabel::getTitle() {
	return label->text();
}
