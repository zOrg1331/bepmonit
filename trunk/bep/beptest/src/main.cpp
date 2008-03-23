#include <QApplication>
#include "beptest.h"

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);
	beptest *mw = new beptest();
	mw->show();
	return app.exec();
}
