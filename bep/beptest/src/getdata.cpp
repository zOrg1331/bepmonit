#include <QtCore>

#include "getdata.h"

GETDATA::GETDATA(DATA *DataValues) : QObject() {
	dataValues = DataValues;
	tcpSocket = new QTcpSocket;
}

void GETDATA::setSocket(QTcpSocket *TcpSocket) {
	tcpSocket = TcpSocket;
	blockSize = 0;
}

void GETDATA::readData() {
	QFile File("./data.txt");
	if (!File.open(QIODevice::ReadOnly | QIODevice::Text))
		return;
	QTextStream file(&File);

	dataValues->setLdefState(file.readLine().toInt());
// 	dataValues->setLdefOff(file.readLine().toInt());

// 	dataValues->setACOff(file.readLine().toInt());
	dataValues->setACU(file.readLine().toFloat());
// 	dataValues->setACHz(file.readLine().toFloat());

	dataValues->setKNSOff(1, file.readLine().toInt());
// 	dataValues->setKNSNorma(1, file.readLine().toInt());
	dataValues->setKNSAvar(1, file.readLine().toInt());
	dataValues->setKNSAvarseti(1, file.readLine().toInt());
	dataValues->setKNSOgran(1, file.readLine().toInt());
	dataValues->setKNSPeregrev(1, file.readLine().toInt());
	dataValues->setKNSTemp(1, file.readLine().toFloat());

	dataValues->setKNSOff(2, file.readLine().toInt());
// 	dataValues->setKNSNorma(2, file.readLine().toInt());
	dataValues->setKNSAvar(2, file.readLine().toInt());
	dataValues->setKNSAvarseti(2, file.readLine().toInt());
	dataValues->setKNSOgran(2, file.readLine().toInt());
	dataValues->setKNSPeregrev(2, file.readLine().toInt());
	dataValues->setKNSTemp(2, file.readLine().toFloat());

	dataValues->setKNSOff(3, file.readLine().toInt());
// 	dataValues->setKNSNorma(3, file.readLine().toInt());
	dataValues->setKNSAvar(3, file.readLine().toInt());
	dataValues->setKNSAvarseti(3, file.readLine().toInt());
	dataValues->setKNSOgran(3, file.readLine().toInt());
	dataValues->setKNSPeregrev(3, file.readLine().toInt());
	dataValues->setKNSTemp(3, file.readLine().toFloat());

	dataValues->setKNSOff(4, file.readLine().toInt());
// 	dataValues->setKNSNorma(4, file.readLine().toInt());
	dataValues->setKNSAvar(4, file.readLine().toInt());
	dataValues->setKNSAvarseti(4, file.readLine().toInt());
	dataValues->setKNSOgran(4, file.readLine().toInt());
	dataValues->setKNSPeregrev(4, file.readLine().toInt());
	dataValues->setKNSTemp(4, file.readLine().toFloat());

	dataValues->setAKBOff(1, file.readLine().toInt());
// 	dataValues->setAKBCharging(1, file.readLine().toInt());
// 	dataValues->setAKBDischarging(1, file.readLine().toInt());
// 	dataValues->setAKBFulldischarg(1, file.readLine().toInt());
// 	dataValues->setAKBTrening(1, file.readLine().toInt());
	dataValues->setAKBU1(1, file.readLine().toFloat());
	dataValues->setAKBU2(1, file.readLine().toFloat());
	dataValues->setAKBU3(1, file.readLine().toFloat());
	dataValues->setAKBU4(1, file.readLine().toFloat());
	dataValues->setAKBU5(1, file.readLine().toFloat());
	dataValues->setAKBI(1, file.readLine().toFloat());
	dataValues->setAKBTemp(1, file.readLine().toFloat());

	dataValues->setAKBOff(2, file.readLine().toInt());
// 	dataValues->setAKBCharging(2, file.readLine().toInt());
// 	dataValues->setAKBDischarging(2, file.readLine().toInt());
// 	dataValues->setAKBFulldischarg(2, file.readLine().toInt());
// 	dataValues->setAKBTrening(2, file.readLine().toInt());
	dataValues->setAKBU1(2, file.readLine().toFloat());
	dataValues->setAKBU2(2, file.readLine().toFloat());
	dataValues->setAKBU3(2, file.readLine().toFloat());
	dataValues->setAKBU4(2, file.readLine().toFloat());
	dataValues->setAKBU5(2, file.readLine().toFloat());
	dataValues->setAKBI(2, file.readLine().toFloat());
	dataValues->setAKBTemp(2, file.readLine().toFloat());

	dataValues->setLoadOff(file.readLine().toInt());
	dataValues->setLoadI(file.readLine().toFloat());

// 	dataValues->setLoad1Off(file.readLine().toInt());
	dataValues->setLoad1State(file.readLine().toInt());
// 	dataValues->setLoad1U(file.readLine().toFloat());
// 	dataValues->setLoad1I(file.readLine().toFloat());

// 	dataValues->setLoad2Off(file.readLine().toInt());
	dataValues->setLoad2State(file.readLine().toInt());
// 	dataValues->setLoad2U(file.readLine().toFloat());
// 	dataValues->setLoad2I(file.readLine().toFloat());

// 	dataValues->setLoad3Off(file.readLine().toInt());
	dataValues->setLoad3State(file.readLine().toInt());
// 	dataValues->setLoad3U(file.readLine().toFloat());
// 	dataValues->setLoad3I(file.readLine().toFloat());

	dataValues->setCoolerOff(file.readLine().toInt());
	dataValues->setCoolerForcedOn(file.readLine().toInt());

	dataValues->setExitU(file.readLine().toFloat());

	File.close();

	if (tcpSocket) {
		QDataStream in(tcpSocket);
		in.setVersion(QDataStream::Qt_4_0);

		if (blockSize == 0) {
			if (tcpSocket->bytesAvailable() < (int)sizeof(quint64))
				return;

			in >> blockSize;
		}

		if (tcpSocket->bytesAvailable() < blockSize)
			return;

		QString newData;
		in >> newData;
		for (int i = 0; i < newData.split(";").size()-1; i += 2) {
			QString parametr = newData.split(";").at(i);
			QString value = newData.split(";").at(i+1);
			if (parametr == "KNS1Off") dataValues->setKNSOff(1, value.toInt());
			if (parametr == "KNS2Off") dataValues->setKNSOff(2, value.toInt());
			if (parametr == "KNS3Off") dataValues->setKNSOff(3, value.toInt());
			if (parametr == "KNS4Off") dataValues->setKNSOff(4, value.toInt());
			if (parametr == "AKB1Off") dataValues->setAKBOff(1, value.toInt());
			if (parametr == "AKB2Off") dataValues->setAKBOff(2, value.toInt());
			if (parametr == "LoadOff") dataValues->setLoadOff(value.toInt());
			if (parametr == "CoolerForcedOn") dataValues->setCoolerForcedOn(value.toInt());
		}
		blockSize = 0;
	}
}
