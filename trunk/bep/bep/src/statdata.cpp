#include <QtCore>
#include "statdata.h"

statdata::statdata() : QObject() {

}

statdata::~statdata() {

}

void statdata::addValue(const char *Name, int num, float value) {
	QString name = Name;
	QTime tmpTime = time[name][num].last();
	if (tmpTime.msecsTo(time[name][num].at(0)) >= 3600000) {
		data[name][num].resize(0);
		time[name][num].resize(0);
	}
	data[name][num].append(value);
	time[name][num].append(QTime::currentTime());
}

QVector<float> *statdata::getData(const char *Name, int Num) {
	return &data[Name][Num];
}

QVector<QTime> *statdata::getTime(const char *Name, int Num) {
	return &time[Name][Num];
}
