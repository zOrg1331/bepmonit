#include <QtGui>
#include "akbcontrol.h"

akbcontrol::akbcontrol(int AKBNum, DATA *DataValues, statdata *Stats, SETDATA *SetDataValues, QWidget *parent) : QWidget(parent) {
	off = false;

	dataValues = DataValues;
	AkbNum = AKBNum;
	setDataValues = SetDataValues;

	chartU = new ZChart();
	chartU->setBorderType(0);
	chartU->setGraphPanelBorderType(0);
	chartU->setMargin(2);
	chartU->setSpacing(2);
	chartU->setFirstText("");
	chartU->setSecondText(" ");
	chartU->setTitle(trUtf8("Напряжение"));
	chartU->setXRange(-10, 10);
	chartU->setYRange(-10, 10);
	chartU->setAxesName(trUtf8("время"), trUtf8("напряжение"));
	chartU->showLegend(false);
	chartU->setAutoscale(true);

	u1Graph = new ZSimpleSeries("");
	u1Graph->setColor(Qt::blue);
	chartU->addSeries(u1Graph);
	u2Graph = new ZSimpleSeries("");
	u2Graph->setColor(Qt::red);
	chartU->addSeries(u2Graph);
	u3Graph = new ZSimpleSeries("");
	u3Graph->setColor(Qt::green);
	chartU->addSeries(u3Graph);
	u4Graph = new ZSimpleSeries("");
	u4Graph->setColor(Qt::magenta);
	chartU->addSeries(u4Graph);
	u5Graph = new ZSimpleSeries("");
	u5Graph->setColor(Qt::yellow);
	chartU->addSeries(u5Graph);

	chartI = new ZChart();
	chartI->setBorderType(0);
	chartI->setGraphPanelBorderType(0);
	chartI->setMargin(2);
	chartI->setSpacing(2);
	chartI->setFirstText("");
	chartI->setSecondText(" ");
	chartI->setTitle(trUtf8("Ток"));
	chartI->setXRange(-10, 10);
	chartI->setYRange(-10, 10);
	chartI->setAxesName(trUtf8("время"), trUtf8("ток"));
	chartI->showLegend(false);
	chartI->setAutoscale(true);

	iGraph = new ZSimpleSeries("");
	iGraph->setColor(Qt::red);
	chartI->addSeries(iGraph);

	chartTemp = new ZChart();
	chartTemp->setBorderType(0);
	chartTemp->setGraphPanelBorderType(0);
	chartTemp->setMargin(2);
	chartTemp->setSpacing(2);
	chartTemp->setFirstText("");
	chartTemp->setSecondText(" ");
	chartTemp->setTitle(trUtf8("Температура"));
	chartTemp->setXRange(-10, 10);
	chartTemp->setYRange(-10, 10);
	chartTemp->setAxesName(trUtf8("время"), trUtf8("температура, %1C:").arg(QChar(0x00B0)));
	chartTemp->showLegend(false);
	chartTemp->setAutoscale(true);

	tempGraph = new ZSimpleSeries("");
	tempGraph->setColor(Qt::red);
	chartI->addSeries(tempGraph);

	stats = Stats;

	u1Data = stats->getData("АКБ;Напряжение1;", AkbNum);
	u1Time = stats->getTime("АКБ;Напряжение1;", AkbNum);
	u2Data = stats->getData("АКБ;Напряжение2;", AkbNum);
	u2Time = stats->getTime("АКБ;Напряжение2;", AkbNum);
	u3Data = stats->getData("АКБ;Напряжение3;", AkbNum);
	u3Time = stats->getTime("АКБ;Напряжение3;", AkbNum);
	u4Data = stats->getData("АКБ;Напряжение4;", AkbNum);
	u4Time = stats->getTime("АКБ;Напряжение4;", AkbNum);
	u5Data = stats->getData("АКБ;Напряжение5;", AkbNum);
	u5Time = stats->getTime("АКБ;Напряжение5;", AkbNum);
	iData = stats->getData("АКБ;Ток;", AkbNum);
	iTime = stats->getTime("АКБ;Ток;", AkbNum);
	tempData = stats->getData("АКБ;Температура;", AkbNum);
	tempTime = stats->getTime("АКБ;Температура;", AkbNum);

	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(updateGraphs()));
	timer->start(1000);

	QGroupBox *gBox1 = new QGroupBox(trUtf8("Состояние"), this);
	gBox1->setAlignment(Qt::AlignCenter);
	QGroupBox *gBox2 = new QGroupBox(trUtf8("Выполнить"), this);
	gBox2->setAlignment(Qt::AlignCenter);
	QGridLayout *gBox1Layout = new QGridLayout;
	QVBoxLayout *gBox2Layout = new QVBoxLayout;
	switchButton = new QPushButton(trUtf8("Отключить"));
	switchButton->setCheckable(true);
	switchButton->setChecked(true);
// 	switchTrenButton = new QPushButton(trUtf8("Вкл. авт. тренинг"));
// 	switchTrenButton->setCheckable(true);
// 	switchTrenButton->setChecked(false);

	QLabel *statusLabel1 = new QLabel(trUtf8("Статус"));
	statusLabel2 = new QLabel(trUtf8(""));
	QLabel *u1sLabel = new QLabel(trUtf8("U1, В"));
	u1Label = new QLabel(trUtf8("0"));
	QLabel *u2sLabel = new QLabel(trUtf8("U2, В"));
	u2Label = new QLabel(trUtf8("0"));
	QLabel *u3sLabel = new QLabel(trUtf8("U3, В"));
	u3Label = new QLabel(trUtf8("0"));
	QLabel *u4sLabel = new QLabel(trUtf8("U4, В"));
	u4Label = new QLabel(trUtf8("0"));
	QLabel *u5sLabel = new QLabel(trUtf8("U5, В"));
	u5Label = new QLabel(trUtf8("0"));
	QLabel *isLabel = new QLabel(trUtf8("I, В"));
	iLabel = new QLabel(trUtf8("0"));
	QLabel *tempsLabel = new QLabel(trUtf8("Темп., %1C:").arg(QChar(0x00B0)));
	tempLabel = new QLabel(trUtf8("0"));

	connect(switchButton, SIGNAL(clicked()), this, SLOT(switchAKB()));
// 	connect(switchTrenButton, SIGNAL(clicked()), this, SLOT(switchAKBTren()));

	gBox1Layout->addWidget(statusLabel1, 0, 0, 1, 1);
	gBox1Layout->addWidget(statusLabel2, 0, 1, 1, 1);
	gBox1Layout->addWidget(u1sLabel, 1, 0, 1, 1);
	gBox1Layout->addWidget(u1Label, 1, 1, 1, 1);
	gBox1Layout->addWidget(u2sLabel, 2, 0, 1, 1);
	gBox1Layout->addWidget(u2Label, 2, 1, 1, 1);
	gBox1Layout->addWidget(u3sLabel, 3, 0, 1, 1);
	gBox1Layout->addWidget(u3Label, 3, 1, 1, 1);
	gBox1Layout->addWidget(u4sLabel, 4, 0, 1, 1);
	gBox1Layout->addWidget(u4Label, 4, 1, 1, 1);
	gBox1Layout->addWidget(u5sLabel, 5, 0, 1, 1);
	gBox1Layout->addWidget(u5Label, 5, 1, 1, 1);
	gBox1Layout->addWidget(isLabel, 6, 0, 1, 1);
	gBox1Layout->addWidget(iLabel, 6, 1, 1, 1);
	gBox1Layout->addWidget(tempsLabel, 7, 0, 1, 1);
	gBox1Layout->addWidget(tempLabel, 7, 1, 1, 1);
	gBox1->setLayout(gBox1Layout);

	gBox2Layout->addWidget(switchButton);
// 	gBox2Layout->addWidget(switchTrenButton);
	gBox2->setLayout(gBox2Layout);

	akbW = new akb(this);

	QVBoxLayout *gBoxesLayout = new QVBoxLayout;
	gBoxesLayout->setSizeConstraint(QLayout::SetFixedSize);
	gBoxesLayout->addWidget(akbW);
	gBoxesLayout->addWidget(gBox1);
	gBoxesLayout->addWidget(gBox2);

	QVBoxLayout *chartsLayout = new QVBoxLayout;
	chartsLayout->setSizeConstraint(QLayout::SetFixedSize);
	chartsLayout->addWidget(chartU);
	chartsLayout->addWidget(chartI);
	chartsLayout->addWidget(chartTemp);

	QHBoxLayout *mainLayout = new QHBoxLayout;
	mainLayout->setSizeConstraint(QLayout::SetFixedSize);
	mainLayout->addLayout(gBoxesLayout);
	mainLayout->addLayout(chartsLayout);

	setLayout(mainLayout);
}

akbcontrol::~akbcontrol() {

}

void akbcontrol::switchAKB() {
	if (switchButton->isChecked()) {
		statusLabel2->setText(trUtf8("<font color=darkRed><b>ВКЛЮЧЕН</b></font>"));
		switchButton->setText(trUtf8("Отключить"));
		akbW->setOff(false);
		dataValues->setAKBOff(AkbNum, false);
		setDataValues->writeData();
	} else {
		statusLabel2->setText(trUtf8("<font color=darkRed><b>ОТКЛЮЧЕН</b></font>"));
		u1Label->setText("<font color=green><b>0</b></font>");
		u2Label->setText("<font color=green><b>0</b></font>");
		u3Label->setText("<font color=green><b>0</b></font>");
		u4Label->setText("<font color=green><b>0</b></font>");
		u5Label->setText("<font color=green><b>0</b></font>");
		iLabel->setText("<font color=green><b>0</b></font>");
		tempLabel->setText("<font color=green><b>25</b></font>");
		switchButton->setText(trUtf8("Включить"));
		akbW->setOff(true);
		dataValues->setAKBOff(AkbNum, true);
		setDataValues->writeData();
	}
}

// void akbcontrol::switchAKBTren() {
// 	if (switchTrenButton->isChecked()) {
// 		statusLabel2->setText(trUtf8("<font color=darkRed>АВТ. ТРЕНИНГ</font>"));
// 		switchTrenButton->setText(trUtf8("Выкл. авт. тренинг"));
// 		akbW->setTrening(true);
// 		dataValues->setAKBTrening(AkbNum, true);
// 		setDataValues->writeData();
// 	} else {
// 		statusLabel2->setText(trUtf8("<font color=darkRed>ВКЛЮЧЕН</font>"));
// 		switchTrenButton->setText(trUtf8("Вкл. авт. тренинг"));
// 		akbW->setTrening(false);
// 		dataValues->setAKBTrening(AkbNum, false);
// 		setDataValues->writeData();
// 	}
// }

void akbcontrol::setOff(bool N) {
	akbW->setOff(N);
	off = N;
	if (N) {
		statusLabel2->setText(trUtf8("<font color=darkRed><b>ОТКЛЮЧЕН</b></font>"));
		u1Label->setText("<font color=green><b>0</b></font>");
		u2Label->setText("<font color=green><b>0</b></font>");
		u3Label->setText("<font color=green><b>0</b></font>");
		u4Label->setText("<font color=green><b>0</b></font>");
		u5Label->setText("<font color=green><b>0</b></font>");
		iLabel->setText("<font color=green><b>0</b></font>");
		tempLabel->setText("<font color=green><b>25</b></font>");
		switchButton->setText(trUtf8("Включить"));
		switchButton->setChecked(false);
	} else {
		statusLabel2->setText(trUtf8("<font color=darkRed><b>ВКЛЮЧЕН</b></font>"));
		switchButton->setText(trUtf8("Выключить"));
		switchButton->setChecked(true);
	}
}

void akbcontrol::setCharging(bool N) {
	akbW->setCharging(N);
	if (N and !off) statusLabel2->setText(trUtf8("<font color=darkRed><b>ЗАРЯД</b></font>"));
}

void akbcontrol::setDischarging(bool N) {
	akbW->setDischarging(N);
	if (N and !off) statusLabel2->setText(trUtf8("<font color=darkRed><b>РАЗРЯД</b></font>"));
}

void akbcontrol::setFulldischarg(bool N) {
	akbW->setFulldischarg(N);
	if (N and !off) statusLabel2->setText(trUtf8("<font color=darkRed><b>ГЛ. РАЗРЯД</b></font>"));
}

// void akbcontrol::setTrening(bool N) {
// 	akbW->setTrening(N);
// 	if (N) {
// 		statusLabel2->setText(trUtf8("<font color=darkRed>АВТ. ТРЕНИНГ</font>"));
// 		switchTrenButton->setText(trUtf8("Выкл. авт. тренинг"));
// 		switchTrenButton->setChecked(true);
// 	} else {
// 		switchTrenButton->setText(trUtf8("Вкл. авт. тренинг"));
// 		switchTrenButton->setChecked(false);
// 	}
// }

void akbcontrol::setU1(float N) {
	akbW->setU1(N);
	if (!off) u1Label->setText(trUtf8("<font color=green><b>%1</b></font>").arg(N));
}

void akbcontrol::setU2(float N) {
	akbW->setU2(N);
	if (!off) u2Label->setText(trUtf8("<font color=green><b>%1</b></font>").arg(N));
}

void akbcontrol::setU3(float N) {
	akbW->setU3(N);
	if (!off) u3Label->setText(trUtf8("<font color=green><b>%1</b></font>").arg(N));
}

void akbcontrol::setU4(float N) {
	akbW->setU4(N);
	if (!off) u4Label->setText(trUtf8("<font color=green><b>%1</b></font>").arg(N));
}

void akbcontrol::setU5(float N) {
	akbW->setU5(N);
	if (!off) u5Label->setText(trUtf8("<font color=green><b>%1</b></font>").arg(N));
}

void akbcontrol::setI(float N) {
	akbW->setI(N);
	if (!off) iLabel->setText(trUtf8("<font color=green><b>%1</b></font>").arg(N));
}

void akbcontrol::setTemp(float N) {
	akbW->setTemp(N);
	if (!off) tempLabel->setText(trUtf8("<font color=green><b>%1</b></font>").arg(N));
}

void akbcontrol::updateGraphs() {
	if (u1Data->size() > 0) {
		u1Graph->clear();
		u2Graph->clear();
		u3Graph->clear();
		u4Graph->clear();
		u5Graph->clear();
		iGraph->clear();
		tempGraph->clear();
		QTime midnight = u1Time->at(0);
		for (int i = 0; i < u1Data->size(); i++) {
			u1Graph->add(abs(u1Time->at(i).msecsTo(midnight)) / 1000.0, u1Data->at(i));
		}
		midnight = u2Time->at(0);
		for (int i = 0; i < u2Data->size(); i++) {
			u2Graph->add(abs(u2Time->at(i).msecsTo(midnight)) / 1000.0, u2Data->at(i));
		}
		midnight = u3Time->at(0);
		for (int i = 0; i < u3Data->size(); i++) {
			u3Graph->add(abs(u3Time->at(i).msecsTo(midnight)) / 1000.0, u3Data->at(i));
		}
		midnight = u4Time->at(0);
		for (int i = 0; i < u4Data->size(); i++) {
			u4Graph->add(abs(u4Time->at(i).msecsTo(midnight)) / 1000.0, u4Data->at(i));
		}
		midnight = u5Time->at(0);
		for (int i = 0; i < u5Data->size(); i++) {
			u5Graph->add(abs(u5Time->at(i).msecsTo(midnight)) / 1000.0, u5Data->at(i));
		}
		midnight = iTime->at(0);
		for (int i = 0; i < iData->size(); i++) {
			iGraph->add(abs(iTime->at(i).msecsTo(midnight)) / 1000.0, iData->at(i));
		}
		midnight = tempTime->at(0);
		for (int i = 0; i < tempData->size(); i++) {
			tempGraph->add(abs(tempTime->at(i).msecsTo(midnight)) / 1000.0, tempData->at(i));
		}
		chartU->autoscale();
		chartU->update();
		chartI->autoscale();
		chartI->update();
		chartTemp->autoscale();
		chartTemp->update();
	}
}
