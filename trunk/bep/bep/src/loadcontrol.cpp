#include <QtGui>
#include "loadcontrol.h"

loadcontrol::loadcontrol(DATA *DataValues, statdata *Stats, SETDATA *SetDataValues, QWidget *parent) : QWidget(parent) {
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
	iGraph->setColor(Qt::blue);
	chartI->addSeries(iGraph);

	stats = Stats;

	uData = stats->getData("Общее;вых. напряжение;", 0);
	uTime = stats->getTime("Общее;вых. напряжение;", 0);
	iData = stats->getData("Нагрузка;Ток;", 0);
	iTime = stats->getTime("Нагрузка;Ток;", 0);

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
	statusLabel2 = new QLabel(trUtf8(""));
	QLabel *avarLabel11 = new QLabel(trUtf8("Авария #1"));
	avarLabel12 = new QLabel(trUtf8(""));
	QLabel *avarLabel21 = new QLabel(trUtf8("Авария #2"));
	avarLabel22 = new QLabel(trUtf8(""));
	QLabel *avarLabel31 = new QLabel(trUtf8("Авария #3"));
	avarLabel32 = new QLabel(trUtf8(""));
	QLabel *uLabel1 = new QLabel(trUtf8("Напряжение выхода, В"));
	uLabel2 = new QLabel(trUtf8("66"));
	QLabel *iLabel1 = new QLabel(trUtf8("Ток нагрузки, А"));
	iLabel2 = new QLabel(trUtf8("15"));
	switchButton = new QPushButton(trUtf8("Отключить"));
	switchButton->setCheckable(true);
	switchButton->setChecked(true);

	connect(switchButton, SIGNAL(clicked()), this, SLOT(switchLoad()));

	gBox1Layout->addWidget(statusLabel1, 0, 0, 1, 1);
	gBox1Layout->addWidget(statusLabel2, 0, 1, 1, 1);
	gBox1Layout->addWidget(avarLabel11, 1, 0, 1, 1);
	gBox1Layout->addWidget(avarLabel12, 1, 1, 1, 1);
	gBox1Layout->addWidget(avarLabel21, 2, 0, 1, 1);
	gBox1Layout->addWidget(avarLabel22, 2, 1, 1, 1);
	gBox1Layout->addWidget(avarLabel31, 3, 0, 1, 1);
	gBox1Layout->addWidget(avarLabel32, 3, 1, 1, 1);
	gBox1Layout->addWidget(uLabel1, 4, 0, 1, 1);
	gBox1Layout->addWidget(uLabel2, 4, 1, 1, 1);
	gBox1Layout->addWidget(iLabel1, 5, 0, 1, 1);
	gBox1Layout->addWidget(iLabel2, 5, 1, 1, 1);
	gBox1->setLayout(gBox1Layout);

	gBox2Layout->addWidget(switchButton);
	gBox2->setLayout(gBox2Layout);

	QVBoxLayout *gBoxesLayout = new QVBoxLayout;
	gBoxesLayout->setSizeConstraint(QLayout::SetFixedSize);
	gBoxesLayout->addWidget(gBox1);
	gBoxesLayout->addWidget(gBox2);

	QVBoxLayout *chartsLayout = new QVBoxLayout;
	chartsLayout->setSizeConstraint(QLayout::SetFixedSize);
	chartsLayout->addWidget(chartU);
	chartsLayout->addWidget(chartI);

	QHBoxLayout *mainLayout = new QHBoxLayout;
	mainLayout->setSizeConstraint(QLayout::SetFixedSize);
	mainLayout->addLayout(gBoxesLayout);
	mainLayout->addLayout(chartsLayout);

	setLayout(mainLayout);
}

loadcontrol::~loadcontrol() {

}

void loadcontrol::setOff(bool N) {
	if (N) {
		statusLabel2->setText(trUtf8("<font color=darkRed><b>ОТКЛЮЧЕН</b></font>"));
		uLabel2->setText("0");
		iLabel2->setText("0");
		switchButton->setChecked(false);
		switchButton->setText(trUtf8("Включить"));
	} else {
		statusLabel2->setText(trUtf8("<font color=darkGreen><b>ВКЛЮЧЕН</b></font>"));
		switchButton->setChecked(true);
		switchButton->setText(trUtf8("Отключить"));
	}
}

void loadcontrol::setState1(bool N) {
	if (N) {
		avarLabel12->setText(trUtf8("<font color=darkGreen><b>РАБОТАЕТ</b></font>"));
	} else {
		avarLabel12->setText(trUtf8("<font color=darkRed><b>АВАРИЯ</b></font>"));
	}
}

void loadcontrol::setState2(bool N) {
	if (N) {
		avarLabel22->setText(trUtf8("<font color=darkGreen><b>РАБОТАЕТ</b></font>"));
	} else {
		avarLabel22->setText(trUtf8("<font color=darkRed><b>АВАРИЯ</b></font>"));
	}
}

void loadcontrol::setState3(bool N) {
	if (N) {
		avarLabel32->setText(trUtf8("<font color=darkGreen><b>РАБОТАЕТ</b></font>"));
	} else {
		avarLabel32->setText(trUtf8("<font color=darkRed><b>АВАРИЯ</b></font>"));
	}
}

void loadcontrol::setExitU(float N) {
	uLabel2->setText(trUtf8("<font color=green><b>%1</b></font>").arg(N));
}

void loadcontrol::setI(float N) {
	iLabel2->setText(trUtf8("<font color=green><b>%1</b></font>").arg(N));
}

void loadcontrol::switchLoad() {
	if (switchButton->isChecked()) {
		switchButton->setText(trUtf8("Отключить"));
		dataValues->setLoadOff(false);
		setDataValues->writeData();
	} else {
		switchButton->setText(trUtf8("Включить"));
		dataValues->setLoadOff(true);
		setDataValues->writeData();
	}
}

void loadcontrol::updateGraphs() {
	if (uData->size() > 0) {
		uGraph->clear();
		iGraph->clear();
		QTime midnight = uTime->at(0);
		for (int i = 0; i < uData->size(); i++) {
			uGraph->add(abs(uTime->at(i).msecsTo(midnight)) / 1000.0, uData->at(i));
		}
		chartU->autoscale();
		chartU->update();
		midnight = iTime->at(0);
		for (int i = 0; i < iData->size(); i++) {
			iGraph->add(abs(iTime->at(i).msecsTo(midnight)) / 1000.0, iData->at(i));
		}
		chartI->autoscale();
		chartI->update();
	}
}
