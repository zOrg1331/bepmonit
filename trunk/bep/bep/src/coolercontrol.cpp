#include <QtGui>
#include "coolercontrol.h"

coolercontrol::coolercontrol(DATA *DataValues, SETDATA *SetDataValues, QWidget *parent) : QWidget(parent) {
	dataValues = DataValues;
	setDataValues = SetDataValues;

	coolerW = new cooler(this);

	QGroupBox *gBox1 = new QGroupBox(trUtf8("Состояние"), this);
	gBox1->setAlignment(Qt::AlignCenter);
	QGroupBox *gBox2 = new QGroupBox(trUtf8("Выполнить"), this);
	gBox2->setAlignment(Qt::AlignCenter);
	QGridLayout *gBox1Layout = new QGridLayout;
	QVBoxLayout *gBox2Layout = new QVBoxLayout;
	QLabel *statusLabel1 = new QLabel(trUtf8("Статус"));
	statusLabel2 = new QLabel(trUtf8(""));
	switchButton = new QPushButton(trUtf8("Отключить"));
	switchButton->setCheckable(true);
	switchButton->setChecked(true);

	connect(switchButton, SIGNAL(clicked()), this, SLOT(switchCooler()));

	gBox1Layout->addWidget(statusLabel1, 0, 0, 1, 1);
	gBox1Layout->addWidget(statusLabel2, 0, 1, 1, 1);
	gBox1->setLayout(gBox1Layout);

	gBox2Layout->addWidget(switchButton);
	gBox2->setLayout(gBox2Layout);

	QVBoxLayout *gBoxesLayout = new QVBoxLayout;
	gBoxesLayout->setSizeConstraint(QLayout::SetFixedSize);
	gBoxesLayout->addWidget(coolerW, 0, Qt::AlignHCenter);
	gBoxesLayout->addWidget(gBox1);
	gBoxesLayout->addWidget(gBox2);

	QHBoxLayout *mainLayout = new QHBoxLayout;
	mainLayout->setSizeConstraint(QLayout::SetFixedSize);
	mainLayout->addLayout(gBoxesLayout);

	setLayout(mainLayout);
}

coolercontrol::~coolercontrol() {

}

void coolercontrol::setOff(bool N) {
	if (N) {
		statusLabel2->setText(trUtf8("<font color=darkRed><b>ОТКЛЮЧЕН</b></font>"));
		coolerW->setOff(N);
		switchButton->setChecked(false);
		switchButton->setText(trUtf8("Включить"));
	} else {
		statusLabel2->setText(trUtf8("<font color=darkGreen><b>ВКЛЮЧЕН</b></font>"));
		coolerW->setOff(N);
		switchButton->setChecked(true);
		switchButton->setText(trUtf8("Отключить"));
	}
}

void coolercontrol::switchCooler() {
	if (switchButton->isChecked()) {
		switchButton->setText(trUtf8("Отключить"));
		dataValues->setCoolerForcedOn(true);
		setDataValues->writeData();
	} else {
		switchButton->setText(trUtf8("Включить"));
		dataValues->setCoolerForcedOn(false);
		setDataValues->writeData();
	}
}
