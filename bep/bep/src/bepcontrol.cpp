#include <QtGui>
#include "bepcontrol.h"

bepcontrol::bepcontrol(QWidget *parent) : QWidget(parent) {
	tcpSocket = new QTcpSocket();
	logger = new log();
	confW = new conf(logger, this);
	stats = new statdata();
	tabs = new QTabWidget(this);
	dataValues = new DATA(logger, stats);
	getDataValues = new GETDATA(dataValues, tcpSocket);
	setDataValues = new SETDATA(dataValues, tcpSocket);
	kns1W = new knscontrol(1, dataValues, stats, setDataValues, this);
	kns2W = new knscontrol(2, dataValues, stats, setDataValues, this);
	kns3W = new knscontrol(3, dataValues, stats, setDataValues, this);
	kns4W = new knscontrol(4, dataValues, stats, setDataValues, this);
	akb1W = new akbcontrol(1, dataValues, stats, setDataValues, this);
	akb2W = new akbcontrol(2, dataValues, stats, setDataValues, this);
	acW = new accontrol(dataValues, stats, setDataValues, this);
	loadW = new loadcontrol(dataValues, stats, setDataValues, this);
	coolerW = new coolercontrol(dataValues, setDataValues, this);
	bepW = new bep(dataValues, kns1W, kns2W, kns3W, kns4W, akb1W, akb2W, acW, loadW, coolerW, logger, confW, setDataValues, this);
	networker = new network(tcpSocket, logger, confW, getDataValues);
	estConnBtn = new QPushButton(trUtf8("Установить соединение"));

	tabs->addTab(confW, trUtf8("Конфигурация"));
	tabs->addTab(bepW, trUtf8("Мониторинг"));
	tabs->addTab(kns1W, trUtf8("КНС1"));
	tabs->addTab(kns2W, trUtf8("КНС2"));
	tabs->addTab(kns3W, trUtf8("КНС3"));
	tabs->addTab(kns4W, trUtf8("КНС4"));
	tabs->addTab(akb1W, trUtf8("АКБ1"));
	tabs->addTab(akb2W, trUtf8("АКБ2"));
	tabs->addTab(acW, trUtf8("Питание"));
	tabs->addTab(loadW, trUtf8("Нагрузка"));
	tabs->addTab(coolerW, trUtf8("Вентилятор"));
	tabs->setCurrentIndex(1);

	connect(bepW, SIGNAL(itemClicked(QString)), this, SLOT(showTab(QString)));

	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(estConnBtn);
	mainLayout->addWidget(tabs);
	mainLayout->setSpacing(1);
	mainLayout->setMargin(1);

	setLayout(mainLayout);

	setWindowTitle(trUtf8("БЭП"));
	resize(800, 670);

	logger->setMsg(4, 0, "приложение;загружено;1");
	logger->setMsg(4, 0, "приложение;нет соединения;0");

	connect(estConnBtn, SIGNAL(clicked()), networker, SLOT(estConnection()));
	connect(tcpSocket, SIGNAL(disconnected()), this, SLOT(lostConnection()));
}

bepcontrol::~bepcontrol() {

}

void bepcontrol::showTab(QString title) {
	if (title == trUtf8("КНС1")) {
		tabs->setCurrentIndex(2);
	}
	if (title == trUtf8("КНС2")) {
		tabs->setCurrentIndex(3);
	}
	if (title == trUtf8("КНС3")) {
		tabs->setCurrentIndex(4);
	}
	if (title == trUtf8("КНС4")) {
		tabs->setCurrentIndex(5);
	}
	if (title == trUtf8("АКБ1")) {
		tabs->setCurrentIndex(6);
	}
	if (title == trUtf8("АКБ2")) {
		tabs->setCurrentIndex(7);
	}
	if (title == trUtf8("Питание")) {
		tabs->setCurrentIndex(8);
	}
	if (title == trUtf8("Нагрузка1")) {
		tabs->setCurrentIndex(9);
	}
	if (title == trUtf8("Нагрузка2")) {
		tabs->setCurrentIndex(9);
	}
	if (title == trUtf8("Нагрузка3")) {
		tabs->setCurrentIndex(9);
	}
	if (title == trUtf8("Вентилятор")) {
		tabs->setCurrentIndex(10);
	}
}

void bepcontrol::lostConnection() {
	logger->setMsg(4, 0, "приложение;нет соединения;0");
}

void bepcontrol::closeEvent(QCloseEvent *event) {
	networker->closeConnection();
}
