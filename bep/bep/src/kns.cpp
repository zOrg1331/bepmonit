#include <QtGui>
#include "kns.h"

kns::kns(QWidget *parent) : QWidget(parent) {
	off = false;
	norm = true;
	avar = false;
	avarseti = false;
	ogran = false;
	peregrev = false;

	tempLCD = new MyLCDNumber();

	tempLCD->setNumDigits(5);
	tempLCD->setSegmentStyle(QLCDNumber::Flat);

	QBrush redBrush = QBrush(Qt::red);
	QBrush greenBrush = QBrush(Qt::darkGreen);
	QBrush blackBrush = QBrush(Qt::gray);
	tempLCD->setPalette(QPalette(greenBrush, blackBrush, blackBrush, blackBrush, redBrush, redBrush, redBrush, redBrush, redBrush));

	tempLCD->move(rect().x() + 30 + 60, rect().y() + 25 + 22 + 22 + 22 + 22 + 26);
	tempLCD->resize(50, 22);
	tempLCD->setParent(this);
	tempLCD->show();

	setCursor(Qt::PointingHandCursor);

	setFixedSize(165, 180);
}

kns::~kns() {

}

void kns::setTitle(QString Title) {
	if (title != Title) {
		title = Title;
		repaint();
	}
}

void kns::setTemp(double temp) {
	tempLCD->display(temp);
	QBrush redBrush = QBrush(Qt::red);
	QBrush greenBrush = QBrush(Qt::darkGreen);
	QBrush blackBrush = QBrush(Qt::gray);
	if (peregrev and !off) {
		tempLCD->setPalette(QPalette(redBrush, blackBrush, blackBrush, blackBrush, redBrush, redBrush, redBrush, redBrush, redBrush));
	} else {
		tempLCD->setPalette(QPalette(greenBrush, blackBrush, blackBrush, blackBrush, redBrush, redBrush, redBrush, redBrush, redBrush));
	}
}

// void kns::setNorma(bool norma) {
// 	if (norm != norma) {
// 		norm = norma;
// 		if (avar or avarseti or ogran or peregrev) norm = false;
// 		repaint();
// 	}
// }

void kns::setAvar(bool Avar) {
	if (avar != Avar) {
		avar = Avar;
		if (avar) norm = false;
		repaint();
	}
}

void kns::setAvarseti(bool Avarseti) {
	if (avarseti != Avarseti) {
		avarseti = Avarseti;
		if (avarseti) norm = false;
		repaint();
	}
}

void kns::setOgran(bool Ogran) {
	if (ogran != Ogran) {
		ogran = Ogran;
		if (ogran) norm = false;
		repaint();
	}
}

void kns::setPeregrev(bool Peregrev) {
	if (peregrev != Peregrev) {
		peregrev = Peregrev;
		if (peregrev) norm = false;
		repaint();
	}
}

void kns::mousePressEvent(QMouseEvent *) {
	emit(itemClicked(title));
}

void kns::setOff(bool Off) {
	if (off != Off) {
		off = Off;
		if (off) {
// 			setNorma(true);
			setAvar(false);
			setAvarseti(false);
			setOgran(false);
			setPeregrev(false);
			setTemp(25);
		}
		repaint();
	}
}

void kns::paintEvent(QPaintEvent *) {
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.setPen(Qt::black);
	// рисуем фон текстурой
	QBrush brush;
	brush.setTexture(QPixmap("./images/bg.png"));
	painter.setBrush(brush);
	painter.drawRect(rect().x(), rect().y(), rect().width() - 1, rect().height() - 1);
	// пишем заголовок
	QRect titleRect = QRect(rect().x(), rect().y() + 2, rect().width(), 15);
	painter.setFont(QFont("Arial", 10));
	painter.drawText(titleRect, Qt::AlignCenter, title);

	// светодиоды рисуем
	painter.setFont(QFont("Arial", 10, QFont::Bold));
	if (!avar and !avarseti and !ogran and !peregrev) {
		norm = true;
	}
	if (norm and !off) {
		painter.setBrush(Qt::green);
		painter.setPen(Qt::darkGreen);
	} else {
		painter.setBrush(Qt::gray);
		painter.setPen(Qt::gray);
	}
	painter.drawEllipse(rect().x() + 30, rect().y() + 25, 15, 15);
	QRect labelRect = QRect(rect().x() + 30 + 15 + 12, rect().y() + 25, rect().width(), 15);
	painter.drawText(labelRect, Qt::AlignLeft, trUtf8("НОРМА"));

	if (!avar or off) {
		painter.setBrush(Qt::gray);
		painter.setPen(Qt::gray);
	} else {
		painter.setBrush(Qt::red);
		painter.setPen(Qt::darkRed);
	}
	painter.drawEllipse(rect().x() + 30, rect().y() + 25 + 22, 15, 15);
	labelRect = QRect(rect().x() + 30 + 15 + 12, rect().y() + 25 + 22 + 1, rect().width(), 15);
	painter.drawText(labelRect, Qt::AlignLeft, trUtf8("АВАРИЯ"));

	if (!avarseti or off) {
		painter.setBrush(Qt::gray);
		painter.setPen(Qt::gray);
	} else {
		painter.setBrush(Qt::red);
		painter.setPen(Qt::darkRed);
	}
	painter.drawEllipse(rect().x() + 30, rect().y() + 25 + 22 + 22, 15, 15);
	labelRect = QRect(rect().x() + 30 + 15 + 12, rect().y() + 25 + 22 + 22 + 1, rect().width(), 15);
	painter.drawText(labelRect, Qt::AlignLeft, trUtf8("АВАРИЯ СЕТИ"));

	if (!ogran or off) {
		painter.setBrush(Qt::gray);
		painter.setPen(Qt::gray);
	} else {
		painter.setBrush(Qt::red);
		painter.setPen(Qt::darkRed);
	}
	painter.drawEllipse(rect().x() + 30, rect().y() + 25 + 22 + 22 + 22, 15, 15);
	labelRect = QRect(rect().x() + 30 + 15 + 12, rect().y() + 25 + 22 + 22 + 22 + 1, rect().width(), 15);
	painter.drawText(labelRect, Qt::AlignLeft, trUtf8("ОГРАНИЧЕНИЕ"));

	if (!peregrev or off) {
		painter.setBrush(Qt::gray);
		painter.setPen(Qt::gray);
	} else {
		painter.setBrush(Qt::red);
		painter.setPen(Qt::darkRed);
	}
	painter.drawEllipse(rect().x() + 30, rect().y() + 25 + 22 + 22 + 22 + 22, 15, 15);
	labelRect = QRect(rect().x() + 30 + 15 + 12, rect().y() + 25 + 22 + 22 + 22 + 22 + 1, rect().width(), 15);
	painter.drawText(labelRect, Qt::AlignLeft, trUtf8("ПЕРЕГРЕВ"));

	// температура
	painter.setFont(QFont("Arial", 10));
	labelRect = QRect(rect().x() + 30, rect().y() + 25 + 22 + 22 + 22 + 22 + 30, rect().width(), 15);
	painter.setPen(Qt::black);
	painter.drawText(labelRect, Qt::AlignLeft, trUtf8("Темп., %1C:").arg(QChar(0x00B0)));

	if (off) {
		painter.setPen(Qt::gray);
		painter.setBrush(Qt::Dense4Pattern);
		painter.drawRect(rect().x(), rect().y(), rect().width() - 1, rect().height() - 1);
	}
}
