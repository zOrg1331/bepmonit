#ifndef STUNNEL_H
#define STUNNEL_H

#include <QtCore>
#include "conf.h"

class stunnel: public QObject {
	Q_OBJECT

	public:
		stunnel(conf *);
		~stunnel();

	protected:

	public slots:
		void setupStunnel();
		void closeStunnel();
		bool running();

	private slots:

	signals:
		void succStarted();

	private:
		conf *confer;
		QProcess *plink;
};

#endif
