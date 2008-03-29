#include "stunnel.h"

stunnel::stunnel(conf *Conf) : QObject() {
	confer = Conf;
	plink = new QProcess(this);
}

stunnel::~stunnel() {
}

void stunnel::setupStunnel() {
#ifdef Q_OS_WIN32
	QString program = "plink.exe";
#endif
#ifdef Q_OS_UNIX
	QString program = "./plink";
#endif
	QStringList env = QProcess::systemEnvironment();
#ifdef Q_OS_WIN32
	env.replaceInStrings(QRegExp("^PATH=(.*)", Qt::CaseInsensitive), "PATH=\\1;.");
#endif
#ifdef Q_OS_UNIX
	env.replaceInStrings(QRegExp("^PATH=(.*)", Qt::CaseInsensitive), "PATH=\\1:.");
#endif
	plink->setEnvironment(env);
	QStringList arguments;
	arguments << "-ssh" << "-l" << confer->getUser() << "-pw" << confer->getPwd() << "-L" << "127.0.0.1:12354:127.0.0.1:12365" << "-N" << confer->getHost();

	plink->setProcessChannelMode(QProcess::MergedChannels);
	plink->start(program, arguments);

	if (!plink->waitForStarted()) {
		QMessageBox msgBox;
		msgBox.setStandardButtons(QMessageBox::Ok);
		msgBox.setText(trUtf8("Не удалось запустить plink! Проверьте, что путь до plink имеется в переменной окружения $PATH."));
		msgBox.setWindowTitle(trUtf8("Ошибка при создании туннеля"));
		msgBox.exec();
		return;
	}
	plink->waitForReadyRead();
	QTimer::singleShot(1000, this, SIGNAL(succStarted()));
	QString out;
	while (plink->bytesAvailable() > 0) {
		out = out + plink->readAll();
	}
	qDebug() << out;
}

void stunnel::closeStunnel() {
	plink->kill();
	plink->waitForFinished();
}

bool stunnel::running() {
	if (plink->state() == QProcess::Running) return true;
	else return false;
}
