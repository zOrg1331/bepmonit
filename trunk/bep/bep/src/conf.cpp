#include <QtGui>
#include "conf.h"

conf::conf(log *Logger, QWidget *parent) : QWidget(parent) {
	logger = Logger;
	settings = new QSettings("NPO ATS", "BEP");

	QDoubleValidator *IChargValidator = new QDoubleValidator(0, 100, 1, this);
	QDoubleValidator *AKBULimitValidator = new QDoubleValidator(0, 100, 1, this);
	QDoubleValidator *tempCritValidator = new QDoubleValidator(0, 100, 1, this);
	QDoubleValidator *tempCoolValidator = new QDoubleValidator(0, 100, 1, this);
	QDoubleValidator *tValidator = new QDoubleValidator(-10, 10, 3, this);


	IChargLabel = new QLabel(trUtf8("Ток заряда, А"));
	ICharg = new QLineEdit(QString("%1").arg(settings->value("ICharg", 20).toDouble()));
	ICharg->setValidator(IChargValidator);
	AKBULimitLabel = new QLabel(trUtf8("Допустимое конечное напряжение АКБ, В"));
	AKBULimit = new QLineEdit(QString("%1").arg(settings->value("AKBULimit", 54).toDouble()));
	AKBULimit->setValidator(AKBULimitValidator);
	tempCorrLabel = new QLabel(trUtf8("Корректирующий температурный фактор заряда"));
	tempCorr = new QLineEdit(QString("%1").arg(settings->value("tempCorr", 1.0).toDouble()));
	tempCorr->setValidator(tValidator);
	tempCritLimitLabel = new QLabel(trUtf8("Температура отключения КНС, %1C").arg(QChar(0x00B0)));
	tempCritLimit = new QLineEdit(QString("%1").arg(settings->value("tempCritLimit", 60).toDouble()));
	tempCritLimit->setValidator(tempCritValidator);
	tempCoolLimitLabel = new QLabel(trUtf8("Температура включения вентилятора, %1C").arg(QChar(0x00B0)));
	tempCoolLimit = new QLineEdit(QString("%1").arg(settings->value("tempCoolLimit", 55).toDouble()));
	tempCoolLimit->setValidator(tempCoolValidator);
	hostLabel = new QLabel(trUtf8("IP адресс МСК"));
	hostEdit = new QLineEdit(QString("%1").arg(settings->value("host", "127.0.0.1").toString()));
	userLabel = new QLabel(trUtf8("Имя пользователя"));
	userEdit = new QLineEdit(QString("%1").arg(settings->value("user", "user").toString()));
	pwdLabel = new QLabel(trUtf8("Пароль"));
	pwdEdit = new QLineEdit(QString("%1").arg(settings->value("pass", "user").toString()));
	pwdEdit->setEchoMode(QLineEdit::Password);
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
	user = userEdit->text();
	pwd = pwdEdit->text();
	logsDir = logsDirEdit->text();

	logger->setLogsDir(logsDir);

	connect(setButton, SIGNAL(clicked()), this, SLOT(setConf()));

	QGridLayout *gridLayout = new QGridLayout;
	gridLayout->setSizeConstraint(QLayout::SetFixedSize);
	gridLayout->addWidget(IChargLabel, 1, 0, 1, 2);
	gridLayout->addWidget(ICharg, 1, 2, 1, 2);
	gridLayout->addWidget(AKBULimitLabel, 2, 0, 1, 2);
	gridLayout->addWidget(AKBULimit, 2, 2, 1, 2);
	gridLayout->addWidget(tempCorrLabel, 3, 0, 1, 2);
	gridLayout->addWidget(tempCorr, 3, 2, 1, 2);
	gridLayout->addWidget(tempCritLimitLabel, 4, 0, 1, 2);
	gridLayout->addWidget(tempCritLimit, 4, 2, 1, 2);
	gridLayout->addWidget(tempCoolLimitLabel, 5, 0, 1, 2);
	gridLayout->addWidget(tempCoolLimit, 5, 2, 1, 2);
	gridLayout->addWidget(hostLabel, 6, 0, 1, 2);
	gridLayout->addWidget(hostEdit, 6, 2, 1, 2);
	gridLayout->addWidget(userLabel, 7, 0, 1, 2);
	gridLayout->addWidget(userEdit, 7, 2, 1, 2);
	gridLayout->addWidget(pwdLabel, 8, 0, 1, 2);
	gridLayout->addWidget(pwdEdit, 8, 2, 1, 2);
// 	gridLayout->addWidget(logsDirLabel, 9, 0, 1, 2);
// 	gridLayout->addWidget(logsDirEdit, 9, 2, 1, 2);
	gridLayout->addWidget(setButton, 9, 1, 1, 2);
	gridLayout->addWidget(bugsEdit, 10, 0, 3, 4);

	QHBoxLayout *vboxLayout = new QHBoxLayout;
	vboxLayout->addStretch(1);
	vboxLayout->addLayout(gridLayout);
	vboxLayout->addStretch(1);

	setLayout(vboxLayout);
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
	user = userEdit->text();
	pwd = pwdEdit->text();
	logsDir = logsDirEdit->text();

	logger->setLogsDir(logsDir);
	logger->setMsg(4, 0, "приложение;реконфигурация;1");

	settings->setValue("ICharg", IChargValue);
	settings->setValue("AKBULimit", AKBULimitValue);
	settings->setValue("tempCorr", tempCorrValue);
	settings->setValue("tempCritLimit", tempCritLimitValue);
	settings->setValue("tempCoolLimit", tempCoolLimitValue);
	settings->setValue("host", host);
	settings->setValue("user", user);
	settings->setValue("pass", pwd);
	settings->setValue("logsDir", logsDir);

	QFile file(logsDir + "./bugs.txt");
	if (!file.open(QIODevice::Append | QIODevice::Text)) {
		QMessageBox msgBox;
		msgBox.setStandardButtons(QMessageBox::Ok);
		msgBox.setText(trUtf8("Не удается открыть на запись файл логов программы bugs.log!"));
		msgBox.setWindowTitle(trUtf8("Ошибка при открытии файла логов программы"));
		msgBox.exec();
	}

	QTextStream out(&file);
	out << bugsEdit->toPlainText() << "\n";
	file.close();

	emit confChanged();
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

QString conf::getUser() {
	return user;
}

QString conf::getPwd() {
	return pwd;
}

QString conf::getLogsDir() {
	return logsDir;
}
