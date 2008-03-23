#include <QtGui>
#include "akb.h"

akb::akb(QWidget *parent) : QWidget(parent) {
	off = false;
	charging = true;
	fulldischarging = false;
// 	trening = false;
	status = trUtf8("ЗАРЯД");
	oldstatus = "";
	title = trUtf8("АКБ");

	u1LCD = new MyLCDNumber();
	u2LCD = new MyLCDNumber();
	u3LCD = new MyLCDNumber();
	u4LCD = new MyLCDNumber();
	u5LCD = new MyLCDNumber();
	iLCD = new MyLCDNumber();
	tempLCD = new MyLCDNumber();

	tempLCD->setNumDigits(5);
	tempLCD->setSegmentStyle(QLCDNumber::Flat);
	u1LCD->setNumDigits(5);
	u1LCD->setSegmentStyle(QLCDNumber::Flat);
	u2LCD->setNumDigits(5);
	u2LCD->setSegmentStyle(QLCDNumber::Flat);
	u3LCD->setNumDigits(5);
	u3LCD->setSegmentStyle(QLCDNumber::Flat);
	u4LCD->setNumDigits(5);
	u4LCD->setSegmentStyle(QLCDNumber::Flat);
	u5LCD->setNumDigits(5);
	u5LCD->setSegmentStyle(QLCDNumber::Flat);
	iLCD->setNumDigits(5);
	iLCD->setSegmentStyle(QLCDNumber::Flat);

	QBrush redBrush = QBrush(Qt::red);
	QBrush greenBrush = QBrush(Qt::darkGreen);
	QBrush blackBrush = QBrush(Qt::gray);
	tempLCD->setPalette(QPalette(greenBrush, blackBrush, blackBrush, blackBrush, redBrush, redBrush, redBrush, redBrush, redBrush));
	u1LCD->setPalette(QPalette(greenBrush, blackBrush, blackBrush, blackBrush, redBrush, redBrush, redBrush, redBrush, redBrush));
	u2LCD->setPalette(QPalette(greenBrush, blackBrush, blackBrush, blackBrush, redBrush, redBrush, redBrush, redBrush, redBrush));
	u3LCD->setPalette(QPalette(greenBrush, blackBrush, blackBrush, blackBrush, redBrush, redBrush, redBrush, redBrush, redBrush));
	u4LCD->setPalette(QPalette(greenBrush, blackBrush, blackBrush, blackBrush, redBrush, redBrush, redBrush, redBrush, redBrush));
	u5LCD->setPalette(QPalette(greenBrush, blackBrush, blackBrush, blackBrush, redBrush, redBrush, redBrush, redBrush, redBrush));
	iLCD->setPalette(QPalette(greenBrush, blackBrush, blackBrush, blackBrush, redBrush, redBrush, redBrush, redBrush, redBrush));

	setCursor(Qt::PointingHandCursor);
	setFixedSize(165, 170);

	u1LCD->move(rect().x() + 30 + 60, rect().y() + 18);
	u1LCD->resize(50, 15);
	u1LCD->setParent(this);
	u1LCD->show();

	u2LCD->move(rect().x() + 30 + 60, rect().y() + 18 + 15 + 2);
	u2LCD->resize(50, 15);
	u2LCD->setParent(this);
	u2LCD->show();

	u3LCD->move(rect().x() + 30 + 60, rect().y() + 18 + 15 + 15 + 4);
	u3LCD->resize(50, 15);
	u3LCD->setParent(this);
	u3LCD->show();

	u4LCD->move(rect().x() + 30 + 60, rect().y() + 18 + 15 + 15 + 15 + 6);
	u4LCD->resize(50, 15);
	u4LCD->setParent(this);
	u4LCD->show();

	u5LCD->move(rect().x() + 30 + 60, rect().y() + 18 + 15 + 15 + 15 + 15 + 8);
	u5LCD->resize(50, 15);
	u5LCD->setParent(this);
	u5LCD->show();

	iLCD->move(rect().x() + 30 + 60, rect().y() + 18 + 15 + 15 + 15 + 15 + 15 + 10);
	iLCD->resize(50, 15);
	iLCD->setParent(this);
	iLCD->show();

	tempLCD->move(rect().x() + 30 + 60, rect().y() + 18 + 15 + 15 + 15 + 15 + 15 + 15 + 12);
	tempLCD->resize(50, 15);
	tempLCD->setParent(this);
	tempLCD->show();
}

akb::~akb() {

}

void akb::setTitle(QString Title) {
	if (title != Title) {
		title = Title;
		repaint();
	}
}

void akb::setTemp(double temp) {
	if (!off) tempLCD->display(temp);
}

void akb::setU1(double u1) {
	if (!off) u1LCD->display(u1);
}

void akb::setU2(double u2) {
	if (!off) u2LCD->display(u2);
}

void akb::setU3(double u3) {
	if (!off) u3LCD->display(u3);
}

void akb::setU4(double u4) {
	if (!off) u4LCD->display(u4);
}

void akb::setU5(double u5) {
	if (!off) u5LCD->display(u5);
}

void akb::setI(double I) {
	if (!off) iLCD->display(I);
}

void akb::setCharging(bool Charging) {
	if (charging != Charging) {
		charging = Charging;
		if (charging and !off) status = trUtf8("ЗАРЯД");
		if (!off) repaint();
	}
}

void akb::setDischarging(bool Discharging) {
	if (discharging != Discharging) {
		discharging = Discharging;
		if (discharging and !fulldischarging and !off) status = trUtf8("РАЗРЯД");
		if (!off) repaint();
	}
}

void akb::setFulldischarg(bool Fulldis) {
	if (fulldischarging != Fulldis) {
		fulldischarging = Fulldis;
		if (fulldischarging and !off) status = trUtf8("ГЛ. РАЗРЯД");
		if (!off) repaint();
	}
}

// void akb::setTrening(bool Trening) {
// 	if (trening != Trening) {
// 		trening = Trening;
// 		if (trening) {
// 			status = trUtf8("ТРЕНИНГ");
// 		} else {
// 			status = trUtf8("ВКЛЮЧЕН");
// 		}
// 		repaint();
// 	}
// }

void akb::mousePressEvent(QMouseEvent *) {
	emit(itemClicked(title));
}

void akb::setOff(bool Off) {
	if (off != Off) {
		if (Off) {
			setTemp(25);
			setU1(0);
			setU2(0);
			setU3(0);
			setU4(0);
			setU5(0);
			setI(0);
			oldstatus = status;
			status = trUtf8("ОТКЛ");
		} else {
			status = oldstatus;
		}
		off = Off;
		repaint();
	}
}

void akb::paintEvent(QPaintEvent *) {
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.setPen(Qt::black);
	// рисуем фон текстурой
	QBrush brush;
	brush.setTexture(QPixmap("./images/bg_akb.png"));
	painter.setBrush(brush);
	painter.drawRect(rect().x(), rect().y(), rect().width() - 1, rect().height() - 1);
	// пишем заголовок
	QRect titleRect = QRect(rect().x(), rect().y() + 2, rect().width(), 15);
	painter.setFont(QFont("Arial", 10));
	painter.drawText(titleRect, Qt::AlignCenter, title);

	// светодиоды рисуем
	painter.setFont(QFont("Arial", 9, QFont::Bold));
	QRect labelRect = QRect(rect().x() + 25, rect().y() + 18, 52, 15);
	painter.drawText(labelRect, Qt::AlignRight, trUtf8("U1, В"));

	labelRect = QRect(rect().x() + 25, rect().y() + 18 + 18, 52, 15);
	painter.drawText(labelRect, Qt::AlignRight, trUtf8("U2, В"));

	labelRect = QRect(rect().x() + 25, rect().y() + 18 + 18 + 18, 52, 15);
	painter.drawText(labelRect, Qt::AlignRight, trUtf8("U3, В"));

	labelRect = QRect(rect().x() + 25, rect().y() + 18 + 18 + 18 + 17, 52, 15);
	painter.drawText(labelRect, Qt::AlignRight, trUtf8("U4, В"));

	labelRect = QRect(rect().x() + 25, rect().y() + 18 + 18 + 18 + 18 + 16, 52, 15);
	painter.drawText(labelRect, Qt::AlignRight, trUtf8("U5, В"));

	labelRect = QRect(rect().x() + 25, rect().y() + 18 + 18 + 18 + 18 + 18 + 14, 52, 15);
	painter.drawText(labelRect, Qt::AlignRight, trUtf8("I, A"));

	// температура
	labelRect = QRect(rect().x() + 25, rect().y() + 18 + 18 + 18 + 18 + 18 + 18 + 13, rect().width(), 15);
	painter.drawText(labelRect, Qt::AlignLeft, trUtf8("Темп., %1C:").arg(QChar(0x00B0)));

	// статус
	labelRect = QRect(rect().x(), rect().y() + 18 + 18 + 18 + 18 + 18 + 18 + 18 + 17, rect().width() / 2, 18);
	painter.setFont(QFont("Arial", 10));
	painter.setPen(Qt::darkBlue);
	painter.drawText(labelRect, Qt::AlignRight, trUtf8("Статус: "));
	labelRect = QRect(rect().x() + rect().width() / 2, rect().y() + 18 + 18 + 18 + 18 + 18 + 18 + 18 + 17, rect().width() / 2, 18);
	painter.setFont(QFont("Arial", 10, QFont::Bold));
	painter.setPen(Qt::darkRed);
	painter.drawText(labelRect, Qt::AlignLeft, status);

	if (off) {
		painter.setPen(Qt::gray);
		painter.setBrush(Qt::Dense4Pattern);
		painter.drawRect(rect().x(), rect().y(), rect().width() - 1, rect().height() - 1);
	}
}
