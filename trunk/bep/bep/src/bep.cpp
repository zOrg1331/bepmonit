#include <QtGui>
#include "bep.h"

bep::bep(DATA *data, knscontrol *Kns1ctrl, knscontrol *Kns2ctrl, knscontrol *Kns3ctrl, knscontrol *Kns4ctrl, akbcontrol *Akb1ctrl, akbcontrol *Akb2ctrl, accontrol *Acctrl, loadcontrol *Loadctrl, coolercontrol *Coolerctrl, log *Logger, conf *ConfData, SETDATA *SetDataValues, QWidget *parent) : QWidget(parent) {
	AKB1charging = true;
	AKB2charging = true;
	AKB1discharging = false;
	AKB2discharging = false;

	dataValues = data;
	kns1ctrl = Kns1ctrl;
	kns2ctrl = Kns2ctrl;
	kns3ctrl = Kns3ctrl;
	kns4ctrl = Kns4ctrl;
	akb1ctrl = Akb1ctrl;
	akb2ctrl = Akb2ctrl;
	acctrl = Acctrl;
	loadctrl = Loadctrl;
	coolerctrl = Coolerctrl;
	logger = Logger;
	confData = ConfData;
	setDataValues = SetDataValues;
	arrowRightCharg = new arrow(this);
	arrowLeftCharg = new arrow(this);
	arrowRightDischarg = new arrow(this);
	arrowLeftDischarg = new arrow(this);
	timerData = new QTimer(this);
	logW = new QTableWidget(this);

	logW->setColumnCount(3);
	logW->setAlternatingRowColors(true);
	logW->setContentsMargins(0, 0, 0, 0);
	logW->verticalHeader()->setVisible(false);
	logW->horizontalHeader()->setVisible(false);
	logW->setFont(QFont("Sans", 8));
	logW->resize(300, 80);
	logW->move(490, 2);
	connect(logger, SIGNAL(newMsg(int, const char *, int)), this, SLOT(newMsg(int, const char *, int)));

	// создаем элементы
	knsW1 = new kns(this);
	knsW2 = new kns(this);
	knsW3 = new kns(this);
	knsW4 = new kns(this);

	akbW1 = new akb(this);
	akbW2 = new akb(this);

	//	empty1 = new empty(this);

	key1 = new key(this);
	key2 = new key(this);
	key3 = new key(this);
	key4 = new key(this);
	key5 = new key(this);
	key6 = new key(this);
	key7 = new key(this);
	key8 = new key(this);

	load1 = new load(this);
	load2 = new load(this);
	load3 = new load(this);

	acpowerW = new acpower(this);

	ldefenseW = new ldefense(this);

	ilabel1 = new ilabel(this);
// 	ilabel2 = new ilabel(this);
	ilabel3 = new ilabel(this);
// 	ilabel4 = new ilabel(this);

	coolerW = new cooler(this);

	// задаем название каждого
	knsW1->setTitle(trUtf8("КНС1"));
	knsW2->setTitle(trUtf8("КНС2"));
	knsW3->setTitle(trUtf8("КНС3"));
	knsW4->setTitle(trUtf8("КНС4"));

	akbW1->setTitle(trUtf8("АКБ1"));
	akbW2->setTitle(trUtf8("АКБ2"));

	key1->setState(true);
	key1->setTitle(trUtf8(""));
	key2->setState(true);
	key2->setTitle(trUtf8(""));
	key3->setState(true);
	key3->setTitle(trUtf8(""));
	key4->setState(true);
	key4->setTitle(trUtf8("Q1"));
	key5->setState(true);
	key5->setTitle(trUtf8("Q2"));
	key6->setState(true);
	key6->setTitle(trUtf8("Q3"));
	key7->setState(true);
	key7->setTitle(trUtf8("Q4"));
	key8->setState(true);
	key8->setTitle(trUtf8("Q5"));

	load1->setTitle(trUtf8("Нагрузка1"));
	load2->setTitle(trUtf8("Нагрузка2"));
	load3->setTitle(trUtf8("Нагрузка3"));

	acpowerW->setTitle(trUtf8("Питание"));

	ldefenseW->setTitle(trUtf8("Грозозащита"));

	ilabel1->setTitle(trUtf8("250 В, 50 Гц"));
// 	ilabel2->setTitle(trUtf8("АКБ1: 250 В, 4 А"));
	ilabel3->setTitle(trUtf8("НАГР: 60 В, 1 А"));
// 	ilabel4->setTitle(trUtf8("АКБ2: 250 В, 4 А"));

	coolerW->setTitle(trUtf8("Вентилятор"));
	coolerW->setOff(false);

	// соединяем сигнал о клике мыши с другим сигналом, который посылаем родительскому виджету
	connect(acpowerW, SIGNAL(itemClicked(QString)), this, SIGNAL(itemClicked(QString)));
	connect(load1, SIGNAL(itemClicked(QString)), this, SIGNAL(itemClicked(QString)));
	connect(load2, SIGNAL(itemClicked(QString)), this, SIGNAL(itemClicked(QString)));
	connect(load3, SIGNAL(itemClicked(QString)), this, SIGNAL(itemClicked(QString)));
	connect(knsW1, SIGNAL(itemClicked(QString)), this, SIGNAL(itemClicked(QString)));
	connect(knsW2, SIGNAL(itemClicked(QString)), this, SIGNAL(itemClicked(QString)));
	connect(knsW3, SIGNAL(itemClicked(QString)), this, SIGNAL(itemClicked(QString)));
	connect(knsW4, SIGNAL(itemClicked(QString)), this, SIGNAL(itemClicked(QString)));
	connect(akbW1, SIGNAL(itemClicked(QString)), this, SIGNAL(itemClicked(QString)));
	connect(akbW2, SIGNAL(itemClicked(QString)), this, SIGNAL(itemClicked(QString)));
	connect(coolerW, SIGNAL(itemClicked(QString)), this, SIGNAL(itemClicked(QString)));

	connect(timerData, SIGNAL(timeout()), this, SLOT(updateData()));
	timerData->start(200);
}

bep::~bep() {

}

void bep::paintEvent(QPaintEvent *) {
	int CENTER = rect().width() / 2 - 40;

	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	QPen pen = QPen(Qt::black);
	pen.setWidth(2);
	painter.setPen(pen);

	// от середины верха до Грозозащиты
	painter.drawLine(CENTER, 0, LDEFCX, LDEFY);
	// от середины низа Грозозащиты до Питания
	painter.drawLine(LDEFCX, LDEFCY, ACCX, ACY);
	// от середины низа Питания уровня над КНСами
	painter.drawLine(ACCX, ACCY, ACCX, ACY + ACH + (KNS1Y - ACY - ACH) / 2);
	// ставим точку!
	painter.drawEllipse(ACCX - 2, ACY + ACH + (KNS1Y - ACY - ACH) / 2 - 2, 4, 4);
	// от середины левого КНС до середины правого КНС на уровне, который выше построен
	painter.drawLine(KNS1CX, ACY + ACH + (KNS1Y - ACY - ACH) / 2, KNS4CX, ACY + ACH + (KNS1Y - ACY - ACH) / 2);
	// спускаемся с вышеначерченной линии на каждый КНС
	painter.drawLine(KNS1CX, ACY + ACH + (KNS1Y - ACY - ACH) / 2, KNS1CX, KNS1Y);
	painter.drawLine(KNS2CX, ACY + ACH + (KNS1Y - ACY - ACH) / 2, KNS2CX, KNS2Y);
	painter.drawLine(KNS3CX, ACY + ACH + (KNS1Y - ACY - ACH) / 2, KNS3CX, KNS3Y);
	painter.drawLine(KNS4CX, ACY + ACH + (KNS1Y - ACY - ACH) / 2, KNS4CX, KNS4Y);
	// ставим точки!
	painter.drawEllipse(KNS2CX - 2, ACY + ACH + (KNS1Y - ACY - ACH) / 2 - 2, 4, 4);
	painter.drawEllipse(KNS3CX - 2, ACY + ACH + (KNS1Y - ACY - ACH) / 2 - 2, 4, 4);
	// линия от середины первого и последнего КНСов на уровне трети расстояния между низом КНСов и первым ключом
	painter.drawLine(KNS1CX, KNS1Y + KNS1H + (KEY1Y - KNS1Y - KNS1H) / 3, KNS4CX, KNS1Y + KNS1H + (KEY1Y - KNS1Y - KNS1H) / 3);
	// спускаемся с вышеначерченной линии на каждый КНС
	painter.drawLine(KNS1CX, KNS1Y + KNS1H + (KEY1Y - KNS1Y - KNS1H) / 3, KNS1CX, KNS1Y + KNS1H);
	painter.drawLine(KNS2CX, KNS1Y + KNS1H + (KEY1Y - KNS1Y - KNS1H) / 3, KNS2CX, KNS2Y + KNS2H);
	painter.drawLine(KNS3CX, KNS1Y + KNS1H + (KEY1Y - KNS1Y - KNS1H) / 3, KNS3CX, KNS3Y + KNS3H);
	painter.drawLine(KNS4CX, KNS1Y + KNS1H + (KEY1Y - KNS1Y - KNS1H) / 3, KNS4CX, KNS4Y + KNS4H);
	// спускаемся с вышеначерченной линии на треть расстояния до первого ключа вниз
	painter.drawLine(CENTER, KNS1Y + KNS1H + (KEY1Y - KNS1Y - KNS1H) / 3, CENTER, KNS1Y + KNS1H + 2*(KEY1Y - KNS1Y - KNS1H) / 3);
	// ставим точки!
	painter.drawEllipse(CENTER - 2, KNS1Y + KNS1H + 2*(KEY1Y - KNS1Y - KNS1H) / 3 - 2, 4, 4);
	painter.drawEllipse(CENTER - 2, KNS1Y + KNS1H + (KEY1Y - KNS1Y - KNS1H) / 3 - 2, 4, 4);
	painter.drawEllipse(KNS2CX - 2, KNS1Y + KNS1H + (KEY1Y - KNS1Y - KNS1H) / 3 - 2, 4, 4);
	painter.drawEllipse(KNS3CX - 2, KNS1Y + KNS1H + (KEY1Y - KNS1Y - KNS1H) / 3 - 2, 4, 4);
	painter.drawEllipse(KEY2CX - 2, KEY2Y + KEY2H - 2, 4, 4);
	// на этом уровне чертим линию от середины первого ключа до середины третьего
	painter.drawLine(KEY1CX, KNS1Y + KNS1H + 2*(KEY1Y - KNS1Y - KNS1H) / 3, KEY3CX, KNS1Y + KNS1H + 2*(KEY1Y - KNS1Y - KNS1H) / 3);
	// спускаемся с вышеначерченной линии на каждый из ключей
	painter.drawLine(KEY1CX, KNS1Y + KNS1H + 2*(KEY1Y - KNS1Y - KNS1H) / 3, KEY1CX, KEY1Y);
	painter.drawLine(KEY2CX, KNS1Y + KNS1H + 2*(KEY1Y - KNS1Y - KNS1H) / 3, KEY2CX, KEY2Y);
	painter.drawLine(KEY3CX, KNS1Y + KNS1H + 2*(KEY1Y - KNS1Y - KNS1H) / 3, KEY3CX, KEY3Y);
	// соединяем первый ключ с четвертым и третий с восьмым
	painter.drawLine(KEY1CX, KEY1Y + KEY1H, KEY4CX, KEY4Y);
	painter.drawLine(KEY3CX, KEY3Y + KEY3H, KEY8CX, KEY8Y);
	// на уровне низа второго ключа рисуем линию от середины пятого до середины седьмого
	painter.drawLine(KEY5CX, KEY2Y + KEY2H, KEY7CX, KEY2Y + KEY2H);
	// спускаемся с вышеначерченной линии на каждый ключ
	painter.drawLine(KEY5CX, KEY2Y + KEY2H, KEY5CX, KEY5Y);
	painter.drawLine(KEY6CX, KEY2Y + KEY2H, KEY6CX, KEY6Y);
	painter.drawLine(KEY7CX, KEY2Y + KEY2H, KEY7CX, KEY7Y);

	// рисуем стрелки заряда/разряда
	painter.setPen(QPen(QColor(79, 106, 25), 1, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin));
	painter.setBrush(QBrush(QColor(122, 163, 39), Qt::SolidPattern));
/*	if (AKB1charging and !AKB1discharging) painter.drawPath(leftChargArrow);
	if (AKB1discharging and !AKB1charging) painter.drawPath(leftDischargArrow);
	if (AKB2charging and !AKB2discharging) painter.drawPath(rightChargArrow);
	if (AKB2discharging and !AKB2charging) painter.drawPath(rightDischargArrow);*/
}

void bep::updateData() {
	ldefenseW->setState(dataValues->getLdefState());
// 	ldefenseW->setOff(dataValues->getLdefOff());

// 	acpowerW->setOff(dataValues->getACOff());
	// на ilabel должно быть
	ilabel1->setTitle(QString(trUtf8("<font color=darkGreen><b>%1</b></font> В")).arg(dataValues->getACU()));
//	acpowerW->setU(dataValues->getACU());
//	acpowerW->setHz(dataValues->getACHz());

// 	acctrl->setOff(dataValues->getACOff());
	acctrl->setU(dataValues->getACU());
// 	acctrl->setHz(dataValues->getACU());

	knsW1->setOff(dataValues->getKNSOff(1));
// 	knsW1->setNorma(dataValues->getKNSNorma(1));
	knsW1->setAvar(dataValues->getKNSAvar(1));
	knsW1->setAvarseti(dataValues->getKNSAvarseti(1));
	knsW1->setOgran(dataValues->getKNSOgran(1));
	knsW1->setPeregrev(dataValues->getKNSPeregrev(1));
	knsW1->setTemp(dataValues->getKNSTemp(1));
	if (dataValues->getKNSTemp(1) >= confData->gettempCoolLimitValue()) {
		dataValues->setCoolerForcedOn(true);
		setDataValues->writeData();
		knsW1->setPeregrev(true);
	}
	if (dataValues->getKNSTemp(1) >= confData->gettempCritLimitValue()) {
		dataValues->setCoolerForcedOn(true);
		dataValues->setKNSOff(1, true);
		setDataValues->writeData();
		knsW1->setOff(true);
	}

	kns1ctrl->setOff(dataValues->getKNSOff(1));
// 	kns1ctrl->setNorma(dataValues->getKNSNorma(1));
	kns1ctrl->setAvar(dataValues->getKNSAvar(1));
	kns1ctrl->setAvarseti(dataValues->getKNSAvarseti(1));
	kns1ctrl->setOgran(dataValues->getKNSOgran(1));
	kns1ctrl->setPeregrev(dataValues->getKNSPeregrev(1));
	kns1ctrl->setTemp(dataValues->getKNSTemp(1));

	knsW2->setOff(dataValues->getKNSOff(2));
// 	knsW2->setNorma(dataValues->getKNSNorma(2));
	knsW2->setAvar(dataValues->getKNSAvar(2));
	knsW2->setAvarseti(dataValues->getKNSAvarseti(2));
	knsW2->setOgran(dataValues->getKNSOgran(2));
	knsW2->setPeregrev(dataValues->getKNSPeregrev(2));
	knsW2->setTemp(dataValues->getKNSTemp(2));
	if (dataValues->getKNSTemp(2) >= confData->gettempCoolLimitValue()) {
		dataValues->setCoolerForcedOn(true);
		setDataValues->writeData();
		knsW2->setPeregrev(true);
	}
	if (dataValues->getKNSTemp(2) >= confData->gettempCritLimitValue()) {
		dataValues->setCoolerForcedOn(true);
		dataValues->setKNSOff(2, true);
		setDataValues->writeData();
		knsW2->setOff(true);
	}

	kns2ctrl->setOff(dataValues->getKNSOff(2));
// 	kns2ctrl->setNorma(dataValues->getKNSNorma(2));
	kns2ctrl->setAvar(dataValues->getKNSAvar(2));
	kns2ctrl->setAvarseti(dataValues->getKNSAvarseti(2));
	kns2ctrl->setOgran(dataValues->getKNSOgran(2));
	kns2ctrl->setPeregrev(dataValues->getKNSPeregrev(2));
	kns2ctrl->setTemp(dataValues->getKNSTemp(2));

	knsW3->setOff(dataValues->getKNSOff(3));
// 	knsW3->setNorma(dataValues->getKNSNorma(3));
	knsW3->setAvar(dataValues->getKNSAvar(3));
	knsW3->setAvarseti(dataValues->getKNSAvarseti(3));
	knsW3->setOgran(dataValues->getKNSOgran(3));
	knsW3->setPeregrev(dataValues->getKNSPeregrev(3));
	knsW3->setTemp(dataValues->getKNSTemp(3));
	if (dataValues->getKNSTemp(3) >= confData->gettempCoolLimitValue()) {
		dataValues->setCoolerForcedOn(true);
		setDataValues->writeData();
		knsW3->setPeregrev(true);
	}
	if (dataValues->getKNSTemp(3) >= confData->gettempCritLimitValue()) {
		dataValues->setCoolerForcedOn(true);
		dataValues->setKNSOff(3, true);
		setDataValues->writeData();
		knsW3->setOff(true);
	}

	kns3ctrl->setOff(dataValues->getKNSOff(3));
// 	kns3ctrl->setNorma(dataValues->getKNSNorma(3));
	kns3ctrl->setAvar(dataValues->getKNSAvar(3));
	kns3ctrl->setAvarseti(dataValues->getKNSAvarseti(3));
	kns3ctrl->setOgran(dataValues->getKNSOgran(3));
	kns3ctrl->setPeregrev(dataValues->getKNSPeregrev(3));
	kns3ctrl->setTemp(dataValues->getKNSTemp(3));

	knsW4->setOff(dataValues->getKNSOff(4));
// 	knsW4->setNorma(dataValues->getKNSNorma(4));
	knsW4->setAvar(dataValues->getKNSAvar(4));
	knsW4->setAvarseti(dataValues->getKNSAvarseti(4));
	knsW4->setOgran(dataValues->getKNSOgran(4));
	knsW4->setPeregrev(dataValues->getKNSPeregrev(4));
	knsW4->setTemp(dataValues->getKNSTemp(4));
	if (dataValues->getKNSTemp(4) >= confData->gettempCoolLimitValue()) {
		dataValues->setCoolerForcedOn(true);
		setDataValues->writeData();
		knsW4->setPeregrev(true);
	}
	if (dataValues->getKNSTemp(4) >= confData->gettempCritLimitValue()) {
		dataValues->setCoolerForcedOn(true);
		dataValues->setKNSOff(4, true);
		setDataValues->writeData();
		knsW4->setOff(true);
	}

	kns4ctrl->setOff(dataValues->getKNSOff(4));
// 	kns4ctrl->setNorma(dataValues->getKNSNorma(4));
	kns4ctrl->setAvar(dataValues->getKNSAvar(4));
	kns4ctrl->setAvarseti(dataValues->getKNSAvarseti(4));
	kns4ctrl->setOgran(dataValues->getKNSOgran(4));
	kns4ctrl->setPeregrev(dataValues->getKNSPeregrev(4));
	kns4ctrl->setTemp(dataValues->getKNSTemp(4));

	akbW1->setOff(dataValues->getAKBOff(1));
	if (dataValues->getAKBOff(1)) {
		key1->setState(false);
	} else {
		key1->setState(true);
	}
// 	akbW1->setCharging(dataValues->getAKBCharging(1));
// 	akbW1->setDischarging(dataValues->getAKBDischarging(1));
// 	akbW1->setFulldischarg(dataValues->getAKBFulldischarg(1));
// 	akbW1->setTrening(dataValues->getAKBTrening(1));
	akbW1->setU1(dataValues->getAKBU1(1));
	akbW1->setU2(dataValues->getAKBU2(1));
	akbW1->setU3(dataValues->getAKBU3(1));
	akbW1->setU4(dataValues->getAKBU4(1));
	akbW1->setU5(dataValues->getAKBU5(1));
	akbW1->setI(dataValues->getAKBI(1));
	akbW1->setTemp(dataValues->getAKBTemp(1));
	if (dataValues->getAKBI(1) <=  0) {
		akbW1->setDischarging(false);
		akbW1->setFulldischarg(false);
		akbW1->setCharging(true);
	}
	if (dataValues->getAKBI(1) >  0) {
		akbW1->setFulldischarg(false);
		akbW1->setCharging(false);
		akbW1->setDischarging(true);
	}
	if ((dataValues->getAKBI(1) >  0) and((dataValues->getExitU() - confData->getAKBULimitValue()) <= 0.2)) {
		akbW1->setCharging(false);
		akbW1->setDischarging(true);
		akbW1->setFulldischarg(true);
	}

	akb1ctrl->setOff(dataValues->getAKBOff(1));
// 	akb1ctrl->setCharging(dataValues->getAKBCharging(1));
// 	akb1ctrl->setDischarging(dataValues->getAKBDischarging(1));
// 	akb1ctrl->setFulldischarg(dataValues->getAKBFulldischarg(1));
// 	akb1ctrl->setTrening(dataValues->getAKBTrening(1));
	akb1ctrl->setU1(dataValues->getAKBU1(1));
	akb1ctrl->setU2(dataValues->getAKBU2(1));
	akb1ctrl->setU3(dataValues->getAKBU3(1));
	akb1ctrl->setU4(dataValues->getAKBU4(1));
	akb1ctrl->setU5(dataValues->getAKBU5(1));
	akb1ctrl->setI(dataValues->getAKBI(1));
	akb1ctrl->setTemp(dataValues->getAKBTemp(1));
	if (dataValues->getAKBI(1) <=  0) {
		akb1ctrl->setDischarging(false);
		akb1ctrl->setFulldischarg(false);
		akb1ctrl->setCharging(true);
		if (!dataValues->getAKBOff(1)) {
			arrowLeftCharg->setInvisible(false);
			arrowLeftDischarg->setInvisible(true);
			AKB1charging = true;
			AKB1discharging = false;
		}
	}
	if (dataValues->getAKBI(1) >  0) {
		akb1ctrl->setFulldischarg(false);
		akb1ctrl->setCharging(false);
		akb1ctrl->setDischarging(true);
		if (!dataValues->getAKBOff(1)) {
			arrowLeftDischarg->setInvisible(false);
			arrowLeftCharg->setInvisible(true);
			AKB1charging = false;
			AKB1discharging = true;
		}
	}
	if ((dataValues->getAKBI(1) >  0) and((dataValues->getExitU() - confData->getAKBULimitValue()) <= 0.2)) {
		akb1ctrl->setCharging(false);
		akb1ctrl->setDischarging(true);
		akb1ctrl->setFulldischarg(true);
		if (!dataValues->getAKBOff(1)) {
			arrowLeftDischarg->setInvisible(false);
			arrowLeftCharg->setInvisible(true);
			AKB1charging = false;
			AKB1discharging = true;
		}
	}
	if (dataValues->getAKBOff(1)) {
		arrowLeftCharg->setInvisible(true);
		arrowLeftDischarg->setInvisible(true);
		AKB1charging = true;
		AKB1discharging = true;
	}

	akbW2->setOff(dataValues->getAKBOff(2));
	if (dataValues->getAKBOff(2)) {
		key3->setState(false);
	} else {
		key3->setState(true);
	}
// 	akbW2->setCharging(dataValues->getAKBCharging(2));
// 	akbW2->setDischarging(dataValues->getAKBDischarging(2));
// 	akbW2->setFulldischarg(dataValues->getAKBFulldischarg(2));
// 	akbW2->setTrening(dataValues->getAKBTrening(2));
	akbW2->setU1(dataValues->getAKBU1(2));
	akbW2->setU2(dataValues->getAKBU2(2));
	akbW2->setU3(dataValues->getAKBU3(2));
	akbW2->setU4(dataValues->getAKBU4(2));
	akbW2->setU5(dataValues->getAKBU5(2));
	akbW2->setI(dataValues->getAKBI(2));
	akbW2->setTemp(dataValues->getAKBTemp(2));
	if (dataValues->getAKBI(2) <=  0) {
		akbW2->setDischarging(false);
		akbW2->setFulldischarg(false);
		akbW2->setCharging(true);
	}
	if (dataValues->getAKBI(2) >  0) {
		akbW2->setFulldischarg(false);
		akbW2->setCharging(false);
		akbW2->setDischarging(true);
	}
	if ((dataValues->getAKBI(2) >  0) and((dataValues->getExitU() - confData->getAKBULimitValue()) <= 0.2)) {
		akbW2->setCharging(false);
		akbW2->setDischarging(true);
		akbW2->setFulldischarg(true);
	}

	akb2ctrl->setOff(dataValues->getAKBOff(2));
// 	akb2ctrl->setCharging(dataValues->getAKBCharging(2));
// 	akb2ctrl->setDischarging(dataValues->getAKBDischarging(2));
// 	akb2ctrl->setFulldischarg(dataValues->getAKBFulldischarg(2));
// 	akb2ctrl->setTrening(dataValues->getAKBTrening(2));
	akb2ctrl->setU1(dataValues->getAKBU1(2));
	akb2ctrl->setU2(dataValues->getAKBU2(2));
	akb2ctrl->setU3(dataValues->getAKBU3(2));
	akb2ctrl->setU4(dataValues->getAKBU4(2));
	akb2ctrl->setU5(dataValues->getAKBU5(2));
	akb2ctrl->setI(dataValues->getAKBI(2));
	akb2ctrl->setTemp(dataValues->getAKBTemp(2));
	if (dataValues->getAKBI(2) <=  0) {
		akb2ctrl->setDischarging(false);
		akb2ctrl->setFulldischarg(false);
		akb2ctrl->setCharging(true);
		if (!dataValues->getAKBOff(2)) {
			arrowRightCharg->setInvisible(false);
			arrowRightDischarg->setInvisible(true);
			AKB2charging = true;
			AKB2discharging = false;
		}
	}
	if (dataValues->getAKBI(2) >  0) {
		akb2ctrl->setFulldischarg(false);
		akb2ctrl->setCharging(false);
		akb2ctrl->setDischarging(true);
		if (!dataValues->getAKBOff(2)) {
			arrowRightDischarg->setInvisible(false);
			arrowRightCharg->setInvisible(true);
			AKB2charging = false;
			AKB2discharging = true;
		}
	}
	if ((dataValues->getAKBI(2) >  0) and((dataValues->getExitU() - confData->getAKBULimitValue()) <= 0.2)) {
		akb2ctrl->setCharging(false);
		akb2ctrl->setDischarging(true);
		akb2ctrl->setFulldischarg(true);
		if (!dataValues->getAKBOff(2)) {
			arrowRightDischarg->setInvisible(false);
			arrowRightCharg->setInvisible(true);
			AKB2charging = false;
			AKB2discharging = true;
		}
	}
	if (dataValues->getAKBOff(2)) {
		arrowRightDischarg->setInvisible(true);
		arrowRightCharg->setInvisible(true);
		AKB2charging = true;
		AKB2discharging = true;
	}

	load1->setOff(dataValues->getLoadOff());
	load2->setOff(dataValues->getLoadOff());
	load3->setOff(dataValues->getLoadOff());

	loadctrl->setOff(dataValues->getLoadOff());

	if (dataValues->getLoadOff()) {
		key2->setState(false);
	} else {
		key2->setState(true);
	}

	ilabel3->setTitle(QString(trUtf8("<font color=darkGreen><b>%1</b></font> В, <font color=darkGreen><b>%2</b></font> А")).arg(dataValues->getExitU()).arg(dataValues->getLoadI()));

	loadctrl->setExitU(dataValues->getExitU());
	loadctrl->setI(dataValues->getLoadI());

	load1->setState(dataValues->getLoad1State());
	loadctrl->setState1(dataValues->getLoad1State());
	load2->setState(dataValues->getLoad2State());
	loadctrl->setState2(dataValues->getLoad2State());
	load3->setState(dataValues->getLoad3State());
	loadctrl->setState3(dataValues->getLoad3State());

	coolerW->setOff(dataValues->getCoolerOff());
	coolerctrl->setOff(dataValues->getCoolerOff());

	key4->setState(true);
	key5->setState(true);
	key6->setState(true);
	key7->setState(true);
	key8->setState(true);
}

void bep::newMsg(int lvl, const char *Msg, int Num) {
	if (logW->rowCount() > 100) logW->setRowCount(0);
	QString msg = trUtf8(Msg);
	logW->setRowCount(logW->rowCount() + 1);
	QTime time;
	QTableWidgetItem *newItem = new QTableWidgetItem;
	QTableWidgetItem *newItem1 = new QTableWidgetItem;
	QTableWidgetItem *newItem2 = new QTableWidgetItem;
	newItem->setText(time.currentTime().toString("hh:mm:ss.zzz"));
	newItem->setFlags(Qt::ItemIsSelectable);
	logW->setItem(logW->rowCount() - 1, 0, newItem);
	if (Num != 0) {
		newItem1->setTextColor(Qt::black);
		newItem1->setText(msg.split(";").at(0) + QString("%1").arg(Num));
	} else {
		newItem1->setTextColor(Qt::black);
		newItem1->setText(msg.split(";").at(0));
	}
	newItem1->setFlags(Qt::ItemIsSelectable);
	logW->setItem(logW->rowCount() - 1, 1, newItem1);
	if (msg.split(";").at(2) == "1") {
		newItem2->setTextColor(Qt::darkGreen);
		newItem2->setText(msg.split(";").at(1));
	} else {
		newItem2->setTextColor(Qt::red);
		newItem2->setText(msg.split(";").at(1));
	}
	newItem2->setFlags(Qt::ItemIsSelectable);
	logW->setItem(logW->rowCount() - 1, 2, newItem2);
	logW->setRowHeight(logW->rowCount() - 1, 17);
	logW->setColumnWidth(0, 85);
	logW->setColumnWidth(1, 85);
	logW->setColumnWidth(2, 105);
	logW->scrollToBottom();
}

void bep::placeWidgets() {
	// располагаем элементы красиво :-)
	int TOPMARGIN = 6;
	int CENTER = rect().width() / 2 - 40;
	int ACLDEFSPACING = 6;
	int ILABELMARGIN = 6;
	int KNS1ACSPACING = 30;
	int KNSKNSSPACING = 10;
	int KNSKEYSPACING = 30;
	int KEY1KEY4SPACING = 25;
	int KEY2KEY5SPACING = 25;
	int KEY5KEY6SPACING = 110;

	ldefenseW->move(CENTER - ldefenseW->rect().width() / 2, TOPMARGIN);

	acpowerW->move(CENTER - acpowerW->rect().width() / 2,
	               TOPMARGIN + ldefenseW->rect().height() + ACLDEFSPACING);

	ilabel1->move(acpowerW->pos().x() + acpowerW->rect().width() + ILABELMARGIN,
	              acpowerW->pos().y() + acpowerW->rect().height() / 2);
// 	ilabel2->move(key1->pos().x() + key1->rect().width() + ILABELMARGIN, key1->pos().y());
	ilabel3->move(CENTER + 20 + ILABELMARGIN, key2->pos().y());
// 	ilabel4->move(key3->pos().x() + key3->rect().width() + ILABELMARGIN, key3->pos().y());

	knsW1->move(CENTER - 3*KNSKNSSPACING / 2 - 2*knsW1->rect().width(),
	            acpowerW->pos().y() + acpowerW->rect().height() + KNS1ACSPACING);
	knsW2->move(knsW1->pos().x() + knsW1->rect().width() + KNSKNSSPACING,
	            acpowerW->pos().y() + acpowerW->rect().height() + KNS1ACSPACING);
	knsW3->move(knsW2->pos().x() + knsW2->rect().width() + KNSKNSSPACING,
	            acpowerW->pos().y() + acpowerW->rect().height() + KNS1ACSPACING);
	knsW4->move(knsW3->pos().x() + knsW3->rect().width() + KNSKNSSPACING,
	            acpowerW->pos().y() + acpowerW->rect().height() + KNS1ACSPACING);

	key1->move(knsW1->pos().x() + knsW1->rect().width() / 2 - key1->rect().width() / 2,
	           knsW1->pos().y() + knsW1->rect().height() + KNSKEYSPACING);
	key2->move(CENTER - key2->rect().width() / 2,
	           knsW1->pos().y() + knsW1->rect().height() + KNSKEYSPACING);
	key3->move(knsW4->pos().x() + knsW4->rect().width() / 2 - key3->rect().width() / 2,
	           knsW1->pos().y() + knsW1->rect().height() + KNSKEYSPACING);
	key4->move(key1->pos().x() + key1->rect().width() / 2 - key4->rect().width() / 2,
	           key1->pos().y() + key1->rect().height() + KEY1KEY4SPACING);
	key8->move(key3->pos().x() + key3->rect().width() / 2 - key8->rect().width() / 2,
	           key3->pos().y() + key3->rect().height() + KEY1KEY4SPACING);

	// а вот к чему привязывать положение 5, 6 и 7 ключей, непонятно ((
	key5->move(key2->pos().x() + key2->rect().width() / 2 - key5->rect().width() / 2 - KEY5KEY6SPACING,
	           key2->pos().y() + key2->rect().height() + KEY2KEY5SPACING);
	key6->move(key2->pos().x() + key2->rect().width() / 2 - key6->rect().width() / 2,
	           key2->pos().y() + key2->rect().height() + KEY2KEY5SPACING);
	key7->move(key2->pos().x() + key2->rect().width() / 2 - key7->rect().width() / 2 + KEY5KEY6SPACING,
	           key2->pos().y() + key2->rect().height() + KEY2KEY5SPACING);

	akbW1->move(key4->pos().x() + key4->rect().width() / 2 - akbW1->rect().width() / 2,
	            key4->pos().y() + key4->rect().height());
	akbW2->move(key8->pos().x() + key8->rect().width() / 2 - akbW2->rect().width() / 2,
	            key8->pos().y() + key8->rect().height());

	load1->move(key5->pos().x() + key5->rect().width() / 2 - load1->rect().width() / 2,
	            key5->pos().y() + key5->rect().height());
	load2->move(key6->pos().x() + key6->rect().width() / 2 - load2->rect().width() / 2,
	            key6->pos().y() + key6->rect().height());
	load3->move(key7->pos().x() + key7->rect().width() / 2 - load3->rect().width() / 2,
	            key7->pos().y() + key7->rect().height());

	coolerW->move(rect().width() / 2 + 250,	rect().height() / 2 + 25);

	arrowRightCharg->move(0, 0);
	arrowLeftCharg->move(0, 0);
	arrowRightDischarg->move(0, 0);
	arrowLeftDischarg->move(0, 0);

	arrowRightCharg->resize(rect().width(), rect().height());
	arrowLeftCharg->resize(rect().width(), rect().height());
	arrowRightDischarg->resize(rect().width(), rect().height());
	arrowLeftDischarg->resize(rect().width(), rect().height());

	// вычисляем опорные точки, относительно которых в пайнтевенте рисовать потом будем
	LDEFX = ldefenseW->pos().x();
	LDEFCX = ldefenseW->pos().x() + ldefenseW->rect().width() / 2;
	LDEFY = ldefenseW->pos().y();
	LDEFCY = ldefenseW->pos().y() + ldefenseW->rect().height();
	ACCX = acpowerW->pos().x() + acpowerW->rect().width() / 2;
	ACY	= acpowerW->pos().y();
	ACCY = acpowerW->pos().y() + acpowerW->rect().height();
	ACH = acpowerW->rect().height();
	KNS1Y = knsW1->pos().y();
	KNS1CX = knsW1->pos().x() + knsW1->rect().width() / 2;
	KNS1H = knsW1->rect().height();
	KNS2CX = knsW2->pos().x() + knsW2->rect().width() / 2;
	KNS2Y = knsW2->pos().y();
	KNS2H = knsW2->rect().height();
	KNS3CX = knsW3->pos().x() + knsW3->rect().width() / 2;
	KNS3Y = knsW3->pos().y();
	KNS3H = knsW3->rect().height();
	KNS4CX = knsW4->pos().x() + knsW4->rect().width() / 2;
	KNS4Y = knsW4->pos().y();
	KNS4H = knsW4->rect().height();
	KEY1Y = key1->pos().y();
	KEY1H = key1->rect().height();
	KEY1CX = key1->pos().x() + key1->rect().width() / 2;
	KEY2CX = key2->pos().x() + key2->rect().width() / 2;
	KEY2Y = key2->pos().y();
	KEY2H = key2->rect().height();
	KEY3CX = key3->pos().x() + key3->rect().width() / 2;
	KEY3Y = key3->pos().y();
	KEY3H = key3->rect().height();
	KEY4CX = key4->pos().x() + key4->rect().width() / 2;
	KEY4Y = key4->pos().y();
	KEY5CX = key5->pos().x() + key5->rect().width() / 2;
	KEY5Y = key5->pos().y();
	KEY6CX = key6->pos().x() + key6->rect().width() / 2;
	KEY6Y = key6->pos().y();
	KEY7CX = key7->pos().x() + key7->rect().width() / 2;
	KEY7Y = key7->pos().y();
	KEY8CX = key8->pos().x() + key8->rect().width() / 2;
	KEY8Y = key8->pos().y();
	AKB2Y = akbW2->pos().y();
	AKB1Y = akbW1->pos().y();

	// задаем контур стрелок заряда/разряда
	QPainterPath tmp1;
	tmp1.moveTo(CENTER - 2 + 8, KNS1Y + KNS1H + 2*(KEY1Y - KNS1Y - KNS1H)/3-3);
	tmp1.lineTo(KNS4CX + 4 - 35, KNS1Y + KNS1H + 2*(KEY1Y - KNS1Y - KNS1H)/3-3);
	tmp1.lineTo(KNS4CX + 4 - 35, AKB2Y - 15);
	tmp1.lineTo(KNS4CX + 4 + 10 - 35, AKB2Y - 15);
	tmp1.lineTo(KNS4CX - 35, AKB2Y - 3);
	tmp1.lineTo(KNS4CX - 4 - 10 - 35, AKB2Y - 15);
	tmp1.lineTo(KNS4CX - 4 - 35, AKB2Y - 15);
	tmp1.lineTo(KNS4CX - 4 - 35, KNS2Y + KNS1H + 2*(KEY1Y - KNS1Y - KNS1H)/3+3);
	tmp1.lineTo(CENTER - 2 + 8, KNS1Y + KNS1H + 2*(KEY1Y - KNS1Y - KNS1H)/3+3);
	tmp1.closeSubpath();
	rightChargArrow = tmp1;
	arrowRightCharg->setPath(tmp1);

	QPainterPath tmp2;
	tmp2.moveTo(CENTER + 2 - 8, KNS1Y + KNS1H + 2*(KEY1Y - KNS1Y - KNS1H)/3-3);
	tmp2.lineTo(KNS1CX - 4 + 35, KNS1Y + KNS1H + 2*(KEY1Y - KNS1Y - KNS1H)/3-3);
	tmp2.lineTo(KNS1CX - 4 + 35, AKB2Y - 15);
	tmp2.lineTo(KNS1CX - 4 - 10 + 35, AKB2Y - 15);
	tmp2.lineTo(KNS1CX + 35, AKB2Y - 3);
	tmp2.lineTo(KNS1CX + 4 + 10 + 35, AKB2Y - 15);
	tmp2.lineTo(KNS1CX + 4 + 35, AKB2Y - 15);
	tmp2.lineTo(KNS1CX + 4 + 35, KNS2Y + KNS1H + 2*(KEY1Y - KNS1Y - KNS1H)/3+3);
	tmp2.lineTo(CENTER + 2 - 8, KNS1Y + KNS1H + 2*(KEY1Y - KNS1Y - KNS1H)/3+3);
	tmp2.closeSubpath();
	leftChargArrow = tmp2;
	arrowLeftCharg->setPath(leftChargArrow);

	QPainterPath tmp3;
	tmp3.moveTo(CENTER - 2 + 20, KEY2Y + KEY2H - 15);
	tmp3.lineTo(CENTER - 2 + 20, KNS1Y + KNS1H+2*(KEY1Y - KNS1Y-KNS1H)/3-3);
	tmp3.lineTo(KNS4CX + 4 - 35, KNS1Y + KNS1H+2*(KEY1Y - KNS1Y-KNS1H)/3-3);
	tmp3.lineTo(KNS4CX + 4 - 35, AKB2Y - 5);
	tmp3.lineTo(KNS4CX - 4 - 35, AKB2Y - 5);
	tmp3.lineTo(KNS4CX-4-35, KNS2Y + KNS1H + 2*(KEY1Y - KNS1Y - KNS1H)/3+3);
	tmp3.lineTo(CENTER - 2 + 26, KNS1Y + KNS1H + 2*(KEY1Y-KNS1Y-KNS1H)/3+3);
	tmp3.lineTo(CENTER - 2 + 26, KEY2Y + KEY2H - 15);
	tmp3.lineTo(CENTER - 2 + 26 + 10, KEY2Y + KEY2H - 15);
	tmp3.lineTo(CENTER - 2 + 23, KEY2Y + KEY2H - 5);
	tmp3.lineTo(CENTER - 2 + 20 - 10, KEY2Y + KEY2H - 15);
	tmp3.lineTo(CENTER - 2 + 20, KEY2Y + KEY2H - 15);
	tmp3.closeSubpath();
	rightDischargArrow = tmp3;
	arrowRightDischarg->setPath(rightDischargArrow);

	QPainterPath tmp4;
	tmp4.moveTo(CENTER + 2 - 20, KEY2Y + KEY2H - 15);
	tmp4.lineTo(CENTER + 2 - 20, KNS1Y + KNS1H + 2*(KEY1Y-KNS1Y-KNS1H)/3-3);
	tmp4.lineTo(KNS1CX - 4 + 35, KNS1Y + KNS1H + 2*(KEY1Y-KNS1Y-KNS1H)/3-3);
	tmp4.lineTo(KNS1CX - 4 + 35, AKB1Y - 5);
	tmp4.lineTo(KNS1CX + 4 + 35, AKB1Y - 5);
	tmp4.lineTo(KNS1CX + 4 + 35, KNS2Y + KNS1H + 2*(KEY1Y-KNS1Y-KNS1H)/3+3);
	tmp4.lineTo(CENTER + 2 - 26, KNS1Y + KNS1H + 2*(KEY1Y-KNS1Y-KNS1H)/3+3);
	tmp4.lineTo(CENTER + 2 - 26, KEY2Y + KEY2H - 15);
	tmp4.lineTo(CENTER + 2 - 26 - 10, KEY2Y + KEY2H - 15);
	tmp4.lineTo(CENTER + 2 - 23, KEY2Y + KEY2H - 5);
	tmp4.lineTo(CENTER + 2 - 20 + 10, KEY2Y + KEY2H - 15);
	tmp4.lineTo(CENTER + 2 - 20, KEY2Y + KEY2H - 15);
	tmp4.closeSubpath();
	leftDischargArrow = tmp4;
	arrowLeftDischarg->setPath(leftDischargArrow);
}

void bep::resizeEvent(QResizeEvent *) {
	placeWidgets();
}
