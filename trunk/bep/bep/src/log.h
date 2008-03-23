#ifndef LOG_H
#define LOG_H

#include <QtCore>

class log: public QObject {
		Q_OBJECT

	public:
		log();
		~log();

	signals:
		void newMsg(int, const char *, int);

	public slots:
		void setMsg(int, int, const char *);
		void setMsg(int, int, const char *, float);
		void setLogsDir(QString);

	private slots:

	private:
		QString logsDir;

};

#endif
