#include <QtGui>
#include "arrow.h"

arrow::arrow(QWidget *parent) : QWidget(parent) {
	invisible = true;
}

arrow::~arrow() {

}

void arrow::paintEvent(QPaintEvent *) {
	if (!invisible) {
		QPainter painter(this);
		painter.setRenderHint(QPainter::Antialiasing);
		painter.setPen(QPen(QColor(79, 106, 25), 1, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin));
		painter.setBrush(QBrush(QColor(122, 163, 39), Qt::SolidPattern));
		painter.drawPath(path);
	}
}

void arrow::setPath(QPainterPath Path) {
	if (path != Path) {
		path = Path;
		repaint();
	}
}

void arrow::setInvisible(bool Invis) {
	if (invisible != Invis) {
		invisible = Invis;
		repaint();
	}
}
