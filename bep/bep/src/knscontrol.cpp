#include <QtGui>
#include "knscontrol.h"

knscontrol::knscontrol(int KNSNum, DATA *DataValues, statdata *Stats, SETDATA *SetDataValues, QWidget *parent) : QWidget(parent) {
	off = false;
	oldstatus = trUtf8("<b><font color=green>НОРМА</font></b>");

	dataValues = DataValues;
	KnsNum = KNSNum;
	setDataValues = SetDataValues;

	chartTemp = new ZChart();
	chartTemp->setBorderType(0);
	chartTemp->setGraphPanelBorderType(0);
	chartTemp->setMargin(2);
	chartTemp->setSpacing(2);
	chartTemp->setFirstText("");
	chartTemp->setTitle(trUtf8("Температура"));
	chartTemp->setXRange(-10, 10);
	chartTemp->setYRange(-10, 10);
	chartTemp->setAxesName(trUtf8("время"), trUtf8("температура"));
	chartTemp->showLegend(false);
	chartTemp->setAutoscale(true);

	tempGraph = new ZSimpleSeries("");
	tempGraph->setColor(Qt::blue);
	chartTemp->addSeries(tempGraph);

	stats = Stats;

	tempData = stats->getData("КНС;Температура;", KnsNum);
	tempTime = stats->getTime("КНС;Температура;", KnsNum);

	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(updateGraphs()));
	timer->start(1000);

	QGroupBox *gBox1 = new QGroupBox(trUtf8("Состояние"), this);
	gBox1->setAlignment(Qt::AlignCenter);
	QGroupBox *gBox2 = new QGroupBox(trUtf8("Выполнить"), this);
	gBox2->setAlignment(Qt::AlignCenter);
	QGridLayout *gBox1Layout = new QGridLayout;
	QVBoxLayout *gBox2Layout = new QVBoxLayout;
	QLabel *statusLabel1 = new QLabel(trUtf8("Статус"));
	statusLabel2 = new QLabel(trUtf8("<b><font color=green>НОРМА</font></b>"));
	QLabel *tempLabel1 = new QLabel(trUtf8("Темп., %1C:").arg(QChar(0x00B0)));
	tempLabel2 = new QLabel(trUtf8("<b>25</b>"));
	switchButton = new QPushButton(trUtf8("Отключить"));
	switchButton->setCheckable(true);
	switchButton->setChecked(true);

	connect(switchButton, SIGNAL(clicked()), this, SLOT(switchKNS()));

	gBox1Layout->addWidget(statusLabel1, 0, 0, 1, 1);
	gBox1Layout->addWidget(statusLabel2, 0, 1, 1, 1);
	gBox1Layout->addWidget(tempLabel1, 1, 0, 1, 1);
	gBox1Layout->addWidget(tempLabel2, 1, 1, 1, 1);
	gBox1->setLayout(gBox1Layout);

	gBox2Layout->addWidget(switchButton);
	gBox2->setLayout(gBox2Layout);

	knsW = new kns(this);

	QVBoxLayout *gBoxesLayout = new QVBoxLayout;
	gBoxesLayout->setSizeConstraint(QLayout::SetFixedSize);
	gBoxesLayout->addWidget(knsW);
	gBoxesLayout->addWidget(gBox1);
	gBoxesLayout->addWidget(gBox2);

	QVBoxLayout *chartsLayout = new QVBoxLayout;
	chartsLayout->setSizeConstraint(QLayout::SetFixedSize);
	chartsLayout->addWidget(chartTemp);

	QHBoxLayout *mainLayout = new QHBoxLayout;
	mainLayout->setSizeConstraint(QLayout::SetFixedSize);
	mainLayout->addLayout(gBoxesLayout);
	mainLayout->addLayout(chartsLayout);

	setLayout(mainLayout);
}

knscontrol::~knscontrol() {

}

void knscontrol::setOff(bool Off) {
	if (off != Off) {
		off = Off;
		knsW->setOff(Off);
		if (off) {
			oldstatus = statusLabel2->text();
			statusLabel2->setText(trUtf8("<b><font color=darkRed>ОТКЛЮЧЕН</font></b>"));
			switchButton->setChecked(false);
			switchButton->setText(trUtf8("Включить"));
		} else {
			statusLabel2->setText(oldstatus);
			switchButton->setChecked(true);
			switchButton->setText(trUtf8("Выключить"));
		}
	}
}

// void knscontrol::setNorma(bool Norma) {
// 	knsW->setNorma(Norma);
// 	if (Norma) statusLabel2->setText(trUtf8("<b><font color=green>НОРМА</font></b>"));
// }

void knscontrol::setAvar(bool Avar) {
	knsW->setAvar(Avar);
	if (Avar and !off) statusLabel2->setText(trUtf8("<b><font color=darkRed>АВАРИЯ</font></b>"));
}

void knscontrol::setAvarseti(bool Avarseti) {
	knsW->setAvarseti(Avarseti);
	if (Avarseti and !off) statusLabel2->setText(trUtf8("<b><font color=darkRed>АВАРИЯ СЕТИ</font></b>"));
}

void knscontrol::setOgran(bool Ogran) {
	knsW->setOgran(Ogran);
	if (Ogran and !off) statusLabel2->setText(trUtf8("<b><font color=darkRed>ОГРАНИЧЕНИЕ</font></b>"));
}

void knscontrol::setPeregrev(bool Peregrev) {
	knsW->setPeregrev(Peregrev);
	if (Peregrev and !off) statusLabel2->setText(trUtf8("<b><font color=darkRed>ПЕРЕГРЕВ</font></b>"));
}

void knscontrol::setTemp(float Temp) {
	knsW->setTemp(Temp);
	if ((statusLabel2->text() != trUtf8("<b><font color=darkRed>ПЕРЕГРЕВ</font></b>")) or off) {
		tempLabel2->setText(trUtf8("<b><font color=darkGreen>%1</font></b>").arg(Temp));
	} else {
		tempLabel2->setText(trUtf8("<b><font color=darkRed>%1</font></b>").arg(Temp));
	}
}

void knscontrol::switchKNS() {
	if (switchButton->isChecked()) {
		statusLabel2->setText(oldstatus);
		switchButton->setText(trUtf8("Отключить"));
		off = false;
		knsW->setOff(false);
		dataValues->setKNSOff(KnsNum, false);
		setDataValues->writeData();
	} else {
		oldstatus = statusLabel2->text();
		statusLabel2->setText(trUtf8("<b><font color=darkRed>ОТКЛЮЧЕН</font></b>"));
		switchButton->setText(trUtf8("Включить"));
		off = true;
		knsW->setOff(true);
		dataValues->setKNSOff(KnsNum, true);
		setDataValues->writeData();
	}
}

void knscontrol::updateGraphs() {
	if (tempData->size() > 0) {
		tempGraph->clear();
		QTime midnight = tempTime->at(0);
		for (int i = 0; i < tempData->size(); i++) {
			tempGraph->add(abs(tempTime->at(i).msecsTo(midnight)) / 1000.0, tempData->at(i));
		}
		chartTemp->autoscale();
		chartTemp->update();
	}
}
