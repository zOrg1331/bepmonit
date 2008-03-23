#ifndef KEY_H
#define KEY_H

#include <QtGui>

class key: public QWidget {
		Q_OBJECT

	public:
		key(QWidget *parent = 0);
		~key();

	protected:
		void paintEvent(QPaintEvent*);

	signals:

	public slots:
		void setTitle(QString);
		void setState(bool);

	private slots:

	private:
		QString title;
		bool state;

		QFrame *frame;

};

#endif
