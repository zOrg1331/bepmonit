#include <QApplication>
#include "bepcontrol.h"

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);
	bepcontrol *mw = new bepcontrol();
	mw->show();
	return app.exec();
}

