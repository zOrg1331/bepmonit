#ifndef STATDATA_H
#define STATDATA_H

#include <QtCore>

class statdata: public QObject {
		Q_OBJECT

	public:
		statdata();
		~statdata();

		QVector<float> *getData(const char *, int);
		QVector<QTime> *getTime(const char *, int);

	signals:

	public slots:
		void addValue(const char *, int, float);

	private slots:

	private:
		QMap<QString, QMap<int, QVector<float > > > data;
		QMap<QString, QMap<int, QVector<QTime > > > time;

};

#endif
