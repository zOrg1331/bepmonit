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
		int getPort();
		QString getLogsDir();

	protected:

	private slots:
		void setConf();

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
		QLabel *portLabel;
		QLineEdit *portEdit;
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
		int port;
		QString logsDir;
};

#endif
