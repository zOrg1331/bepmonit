#include <QtCore>
#include "log.h"

log::log() : QObject() {

}

log::~log() {

}

void log::setMsg(int lvl, int N, const char *msg) {
	if (lvl == 1) emit newMsg(lvl, msg, N);
//	if (lvl == 3) emit newMsg(lvl, msg, N);
	if (lvl == 4) emit newMsg(lvl, msg, N);

	QFile file(logsDir + "./messages.log");
	if (!file.open(QIODevice::Append | QIODevice::Text))
		return;

	QTextStream out(&file);
	out << QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss.zzz") << " " << trUtf8(msg) << "\n";
	file.close();
}

void log::setMsg(int lvl, int Num, const char *msg, float N) {
	QFile file(logsDir + "./stats.log");
	if (!file.open(QIODevice::Append | QIODevice::Text))
		return;

	QTextStream out(&file);
	out << QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss.zzz") << " " << trUtf8(msg) << " " << N << "\n";
	file.close();
}

void log::setLogsDir(QString LogsDir) {
	logsDir = LogsDir;
}
