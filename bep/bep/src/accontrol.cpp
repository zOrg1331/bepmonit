#include <QtGui>
#include "accontrol.h"

accontrol::accontrol(DATA *DataValues, statdata *Stats, SETDATA *SetDataValues, QWidget *parent) : QWidget(parent) {
	dataValues = DataValues;
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

	uGraph = new ZSimpleSeries("");
	uGraph->setColor(Qt::blue);
	chartU->addSeries(uGraph);

// 	chartHz = new ZChart();
// 	chartHz->setBorderType(0);
// 	chartHz->setGraphPanelBorderType(0);
// 	chartHz->setMargin(2);
// 	chartHz->setSpacing(2);
// 	chartHz->setFirstText("");
// 	chartHz->setTitle(trUtf8("Частота"));
// 	chartHz->setXRange(-10, 10);
// 	chartHz->setYRange(-10, 10);
// 	chartHz->setAxesName(trUtf8("время"), trUtf8("частота"));
// 	chartHz->showLegend(false);
// 	chartHz->setAutoscale(true);
//
// 	hzGraph = new ZSimpleSeries("");
// 	hzGraph->setColor(Qt::red);
// 	chartHz->addSeries(hzGraph);

	stats = Stats;

	uData = stats->getData("Питание;Напряжение;", 0);
	uTime = stats->getTime("Питание;Напряжение;", 0);
// 	hzData = stats->getData("Питание;Частота;", 0);
// 	hzTime = stats->getTime("Питание;Частота;", 0);

	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(updateGraphs()));
	timer->start(1000);

	QGroupBox *gBox1 = new QGroupBox(trUtf8("Состояние"), this);
	gBox1->setAlignment(Qt::AlignCenter);
// 	QGroupBox *gBox2 = new QGroupBox(trUtf8("Выполнить"), this);
// 	gBox2->setAlignment(Qt::AlignCenter);
	QGridLayout *gBox1Layout = new QGridLayout;
// 	QVBoxLayout *gBox2Layout = new QVBoxLayout;
// 	QLabel *statusLabel1 = new QLabel(trUtf8("Статус"));
// 	statusLabel2 = new QLabel(trUtf8(""));
	QLabel *uLabel1 = new QLabel(trUtf8("Напряжение сети, В"));
	uLabel2 = new QLabel(trUtf8("220"));
// 	QLabel *hzLabel1 = new QLabel(trUtf8("Частота, Hz"));
// 	hzLabel2 = new QLabel(trUtf8("50"));
// 	switchButton = new QPushButton(trUtf8("Отключить"));
// 	switchButton->setCheckable(true);
// 	switchButton->setChecked(true);

// 	connect(switchButton, SIGNAL(clicked()), this, SLOT(switchAC()));

// 	gBox1Layout->addWidget(statusLabel1, 0, 0, 1, 1);
// 	gBox1Layout->addWidget(statusLabel2, 0, 1, 1, 1);
	gBox1Layout->addWidget(uLabel1, 1, 0, 1, 1);
	gBox1Layout->addWidget(uLabel2, 1, 1, 1, 1);
// 	gBox1Layout->addWidget(hzLabel1, 2, 0, 1, 1);
// 	gBox1Layout->addWidget(hzLabel2, 2, 1, 1, 1);
	gBox1->setLayout(gBox1Layout);

// 	gBox2Layout->addWidget(switchButton);
// 	gBox2->setLayout(gBox2Layout);

	acpowerW = new acpower(this);

	QVBoxLayout *gBoxesLayout = new QVBoxLayout;
	gBoxesLayout->setSizeConstraint(QLayout::SetFixedSize);
	gBoxesLayout->addWidget(acpowerW, 0, Qt::AlignHCenter);
	gBoxesLayout->addWidget(gBox1);
// 	gBoxesLayout->addWidget(gBox2);

	QVBoxLayout *chartsLayout = new QVBoxLayout;
	chartsLayout->setSizeConstraint(QLayout::SetFixedSize);
	chartsLayout->addWidget(chartU);
// 	chartsLayout->addWidget(chartHz);

	QHBoxLayout *mainLayout = new QHBoxLayout;
	mainLayout->setSizeConstraint(QLayout::SetFixedSize);
	mainLayout->addLayout(gBoxesLayout);
	mainLayout->addLayout(chartsLayout);

	setLayout(mainLayout);
}

accontrol::~accontrol() {

}

// void accontrol::setOff(bool N) {
// 	acpowerW->setOff(N);
// 	if (N) {
// 		statusLabel2->setText(trUtf8("<font color=darkRed>ОТКЛЮЧЕН</font>"));
// 		uLabel2->setText("0");
// 		hzLabel2->setText("0");
// 		switchButton->setChecked(false);
// 		switchButton->setText(trUtf8("Включить"));
// 	} else {
// 		statusLabel2->setText(trUtf8("<font color=darkGreen>ВКЛЮЧЕН</font>"));
// 		switchButton->setChecked(true);
// 		switchButton->setText(trUtf8("Отключить"));
// 	}
// }

void accontrol::setU(float N) {
// 	acpowerW->setU(N);
	uLabel2->setText(trUtf8("<font color=green><b>%1</b></font>").arg(N));
}

// void accontrol::setHz(float N) {
// 	acpowerW->setHz(N);
// 	hzLabel2->setText(trUtf8("%1").arg(N));
// }

// void accontrol::switchAC() {
// 	if (switchButton->isChecked()) {
// 		switchButton->setText(trUtf8("Отключить"));
// 		acpowerW->setOff(false);
// 		dataValues->setACOff(false);
// 		setDataValues->writeData();
// 	} else {
// 		switchButton->setText(trUtf8("Включить"));
// 		acpowerW->setOff(true);
// 		dataValues->setACOff(true);
// 		setDataValues->writeData();
// 	}
// }

void accontrol::updateGraphs() {
	if (uData->size() > 0) {
		uGraph->clear();
// 		hzGraph->clear();
		QTime midnight = uTime->at(0);
		for (int i = 0; i < uData->size(); i++) {
			uGraph->add(abs(uTime->at(i).msecsTo(midnight)) / 1000.0, uData->at(i));
		}
		chartU->autoscale();
		chartU->update();
// 		midnight = hzTime->at(0);
// 		for (int i = 0; i < hzData->size(); i++) {
// 			hzGraph->add(abs(hzTime->at(i).msecsTo(midnight)) / 1000.0, hzData->at(i));
// 		}
// 		chartHz->autoscale();
// 		chartHz->update();
	}
}
