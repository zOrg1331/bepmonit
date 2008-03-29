#include <QApplication>
#include <QPlastiqueStyle>
#include "bepcontrol.h"

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);
	QApplication::setStyle(new QPlastiqueStyle);
	QApplication::setPalette(QPalette(QColor(255, 255, 255, 255)));
	bepcontrol *mw = new bepcontrol();
	mw->show();
	return app.exec();
}

