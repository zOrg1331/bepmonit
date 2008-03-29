#ifndef CONF_H
#define CONF_H

#include <QtGui>

#include "log.h"

class conf: public QWidget {
		Q_OBJECT

	public:
		conf(log *, QWidget *parent = 0);
		~conf();

		float getIChargValue();
		float getAKBULimitValue();
		float gettempCorrValue();
		float gettempCritLimitValue();
		float gettempCoolLimitValue();
		QString getHost();
		QString getUser();
		QString getPwd();
		QString getLogsDir();

	protected:

	private slots:
		void setConf();

	signals:
		void confChanged();

	private:
		log *logger;
		QSettings *settings;

		QLabel *IChargLabel;
		QLineEdit *ICharg;
		QLabel *AKBULimitLabel;
		QLineEdit *AKBULimit;
		QLabel *tempCorrLabel;
		QLineEdit *tempCorr;
		QLabel *tempCritLimitLabel;
		QLineEdit *tempCritLimit;
		QLabel *tempCoolLimitLabel;
		QLineEdit *tempCoolLimit;
		QLabel *hostLabel;
		QLineEdit *hostEdit;
		QLabel *userLabel;
		QLineEdit *userEdit;
		QLabel *pwdLabel;
		QLineEdit *pwdEdit;
		QLabel *logsDirLabel;
		QLineEdit *logsDirEdit;
		QPushButton *setButton;
		QTextEdit *bugsEdit;

		float IChargValue;
		float AKBULimitValue;
		float tempCorrValue;
		float tempCritLimitValue;
		float tempCoolLimitValue;
		QString host;
		QString user;
		QString pwd;
		QString logsDir;
};

#endif
