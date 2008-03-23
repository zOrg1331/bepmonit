#include <QtGui>
#include "conf.h"

conf::conf(log *Logger, QWidget *parent) : QWidget(parent) {
	logger = Logger;
	settings = new QSettings("NPO ATS", "BEP");

	IChargLabel = new QLabel(trUtf8("Ток заряда, А"));
	ICharg = new QLineEdit(QString("%1").arg(settings->value("ICharg", 20).toDouble()));
	AKBULimitLabel = new QLabel(trUtf8("Допустимое конечное напряжение АКБ, В"));
	AKBULimit = new QLineEdit(QString("%1").arg(settings->value("AKBULimit", 54).toDouble()));
	tempCorrLabel = new QLabel(trUtf8("Корректирующий температурный фактор заряда"));
	tempCorr = new QLineEdit(QString("%1").arg(settings->value("tempCorr", 1.0).toDouble()));
	tempCritLimitLabel = new QLabel(trUtf8("Температура отключения КНС, %1C").arg(QChar(0x00B0)));
	tempCritLimit = new QLineEdit(QString("%1").arg(settings->value("tempCritLimit", 60).toDouble()));
	tempCoolLimitLabel = new QLabel(trUtf8("Температура включения вентилятора, %1C").arg(QChar(0x00B0)));
	tempCoolLimit = new QLineEdit(QString("%1").arg(settings->value("tempCoolLimit", 55).toDouble()));
	hostLabel = new QLabel(trUtf8("IP адресс МСК"));
	hostEdit = new QLineEdit(QString("%1").arg(settings->value("host", "127.0.0.1").toString()));
	portLabel = new QLabel(trUtf8("Порт МСК"));
	portEdit = new QLineEdit(QString("%1").arg(settings->value("port", 12365).toInt()));
	logsDirLabel = new QLabel(trUtf8("Директория с лог-файлами"));
	logsDirEdit = new QLineEdit(QString("%1").arg(settings->value("logsDir", "./").toString()));
	setButton = new QPushButton(trUtf8("Сохранить настройки"));
	bugsEdit = new QTextEdit(trUtf8("Сюда пишите замечания и ошибки по работе программы.\nСохранение произойдет после нажатия кнопки \"Сохранить настройки\""));

	IChargValue = ICharg->text().toFloat();
	AKBULimitValue = AKBULimit->text().toFloat();
	tempCorrValue = tempCorr->text().toFloat();
	tempCritLimitValue = tempCritLimit->text().toFloat();
	tempCoolLimitValue = tempCoolLimit->text().toFloat();
	host = hostEdit->text();
	port = portEdit->text().toInt();
	logsDir = logsDirEdit->text();

	logger->setLogsDir(logsDir);

	connect(setButton, SIGNAL(clicked()), this, SLOT(setConf()));

	QGridLayout *mainLayout = new QGridLayout;
	mainLayout->setSizeConstraint(QLayout::SetFixedSize);
	mainLayout->addWidget(IChargLabel, 1, 0, 1, 2);
	mainLayout->addWidget(ICharg, 1, 2, 1, 2);
	mainLayout->addWidget(AKBULimitLabel, 2, 0, 1, 2);
	mainLayout->addWidget(AKBULimit, 2, 2, 1, 2);
	mainLayout->addWidget(tempCorrLabel, 3, 0, 1, 2);
	mainLayout->addWidget(tempCorr, 3, 2, 1, 2);
	mainLayout->addWidget(tempCritLimitLabel, 4, 0, 1, 2);
	mainLayout->addWidget(tempCritLimit, 4, 2, 1, 2);
	mainLayout->addWidget(tempCoolLimitLabel, 5, 0, 1, 2);
	mainLayout->addWidget(tempCoolLimit, 5, 2, 1, 2);
	mainLayout->addWidget(hostLabel, 6, 0, 1, 2);
	mainLayout->addWidget(hostEdit, 6, 2, 1, 2);
	mainLayout->addWidget(portLabel, 7, 0, 1, 2);
	mainLayout->addWidget(portEdit, 7, 2, 1, 2);
	mainLayout->addWidget(logsDirLabel, 8, 0, 1, 2);
	mainLayout->addWidget(logsDirEdit, 8, 2, 1, 2);
	mainLayout->addWidget(setButton, 9, 1, 1, 2);
	mainLayout->addWidget(bugsEdit, 12, 0, 3, 4);
	setLayout(mainLayout);
}

conf::~conf() {

}

void conf::setConf() {
	IChargValue = ICharg->text().toFloat();
	AKBULimitValue = AKBULimit->text().toFloat();
	tempCorrValue = tempCorr->text().toFloat();
	tempCritLimitValue = tempCritLimit->text().toFloat();
	tempCoolLimitValue = tempCoolLimit->text().toFloat();
	host = hostEdit->text();
	port = portEdit->text().toInt();
	logsDir = logsDirEdit->text();

	logger->setLogsDir(logsDir);
	logger->setMsg(4, 0, "приложение;реконфигурация;1");

	settings->setValue("ICharg", IChargValue);
	settings->setValue("AKBULimit", AKBULimitValue);
	settings->setValue("tempCorr", tempCorrValue);
	settings->setValue("tempCritLimit", tempCritLimitValue);
	settings->setValue("tempCoolLimit", tempCoolLimitValue);
	settings->setValue("host", host);
	settings->setValue("port", port);
	settings->setValue("logsDir", logsDir);

	QFile file(logsDir + "./bugs.txt");
	if (!file.open(QIODevice::Append | QIODevice::Text))
		return;

	QTextStream out(&file);
	out << bugsEdit->toPlainText() << "\n";
	file.close();
}

float conf::getIChargValue() {
	return IChargValue;
}

float conf::getAKBULimitValue() {
	return AKBULimitValue;
}

float conf::gettempCorrValue() {
	return tempCorrValue;
}

float conf::gettempCritLimitValue() {
	return tempCritLimitValue;
}

float conf::gettempCoolLimitValue() {
	return tempCoolLimitValue;
}

QString conf::getHost() {
	return host;
}

int conf::getPort() {
	return port;
}

QString conf::getLogsDir() {
	return logsDir;
}
