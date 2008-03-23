#include <QtCore>

#include "setdata.h"

SETDATA::SETDATA(DATA *DataValues, QTcpSocket *TCPSocket) : QObject() {
	dataValues = DataValues;
	tcpSocket = TCPSocket;
}

void SETDATA::writeData() {
	QByteArray block;
	QDataStream out(&block, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_4_0);
	out << (quint64)0;

	out << QString("KNS1Off;%1;").arg(dataValues->getKNSOff(1)) +
			QString("KNS2Off;%1;").arg(dataValues->getKNSOff(2)) +
			QString("KNS3Off;%1;").arg(dataValues->getKNSOff(3)) +
			QString("KNS4Off;%1;").arg(dataValues->getKNSOff(4)) +
			QString("AKB1Off;%1;").arg(dataValues->getAKBOff(1)) +
			QString("AKB2Off;%1;").arg(dataValues->getAKBOff(2)) +
			QString("LoadOff;%1;").arg(dataValues->getLoadOff()) +
			QString("CoolerForcedOn;%1;").arg(dataValues->getCoolerForcedOn());

	out.device()->seek(0);
	out << (quint64)(block.size() - sizeof(quint64));

	tcpSocket->write(block);
}

void SETDATA::writeDataF() {
	QFile File("./data.txt");
	if (!File.open(QIODevice::WriteOnly | QIODevice::Text))
		return;
	QTextStream file(&File);

	file << dataValues->getLdefState() << "\n";
// 	file << dataValues->getLdefOff() << "\n";

// 	file << dataValues->getACOff() << "\n";
	file << dataValues->getACU() << "\n";
// 	file << dataValues->getACHz() << "\n";

	file << dataValues->getKNSOff(1) << "\n";
// 	file << dataValues->getKNSNorma(1) << "\n";
	file << dataValues->getKNSAvar(1) << "\n";
	file << dataValues->getKNSAvarseti(1) << "\n";
	file << dataValues->getKNSOgran(1) << "\n";
	file << dataValues->getKNSPeregrev(1) << "\n";
	file << dataValues->getKNSTemp(1) << "\n";

	file << dataValues->getKNSOff(2) << "\n";
// 	file << dataValues->getKNSNorma(2) << "\n";
	file << dataValues->getKNSAvar(2) << "\n";
	file << dataValues->getKNSAvarseti(2) << "\n";
	file << dataValues->getKNSOgran(2) << "\n";
	file << dataValues->getKNSPeregrev(2) << "\n";
	file << dataValues->getKNSTemp(2) << "\n";

	file << dataValues->getKNSOff(3) << "\n";
// 	file << dataValues->getKNSNorma(3) << "\n";
	file << dataValues->getKNSAvar(3) << "\n";
	file << dataValues->getKNSAvarseti(3) << "\n";
	file << dataValues->getKNSOgran(3) << "\n";
	file << dataValues->getKNSPeregrev(3) << "\n";
	file << dataValues->getKNSTemp(3) << "\n";

	file << dataValues->getKNSOff(4) << "\n";
// 	file << dataValues->getKNSNorma(4) << "\n";
	file << dataValues->getKNSAvar(4) << "\n";
	file << dataValues->getKNSAvarseti(4) << "\n";
	file << dataValues->getKNSOgran(4) << "\n";
	file << dataValues->getKNSPeregrev(4) << "\n";
	file << dataValues->getKNSTemp(4) << "\n";

	file << dataValues->getAKBOff(1) << "\n";
// 	file << dataValues->getAKBCharging(1) << "\n";
// 	file << dataValues->getAKBDischarging(1) << "\n";
// 	file << dataValues->getAKBFulldischarg(1) << "\n";
// 	file << dataValues->getAKBTrening(1) << "\n";
	file << dataValues->getAKBU1(1) << "\n";
	file << dataValues->getAKBU2(1) << "\n";
	file << dataValues->getAKBU3(1) << "\n";
	file << dataValues->getAKBU4(1) << "\n";
	file << dataValues->getAKBU5(1) << "\n";
	file << dataValues->getAKBI(1) << "\n";
	file << dataValues->getAKBTemp(1) << "\n";

	file << dataValues->getAKBOff(2) << "\n";
// 	file << dataValues->getAKBCharging(2) << "\n";
// 	file << dataValues->getAKBDischarging(2) << "\n";
// 	file << dataValues->getAKBFulldischarg(2) << "\n";
// 	file << dataValues->getAKBTrening(2) << "\n";
	file << dataValues->getAKBU1(2) << "\n";
	file << dataValues->getAKBU2(2) << "\n";
	file << dataValues->getAKBU3(2) << "\n";
	file << dataValues->getAKBU4(2) << "\n";
	file << dataValues->getAKBU5(2) << "\n";
	file << dataValues->getAKBI(2) << "\n";
	file << dataValues->getAKBTemp(2) << "\n";

	file << dataValues->getLoadOff() << "\n";
	file << dataValues->getLoadI() << "\n";

// 	file << dataValues->getLoad1Off() << "\n";
	file << dataValues->getLoad1State() << "\n";
// 	file << dataValues->getLoad1U() << "\n";
// 	file << dataValues->getLoad1I() << "\n";

// 	file << dataValues->getLoad2Off() << "\n";
	file << dataValues->getLoad2State() << "\n";
// 	file << dataValues->getLoad2U() << "\n";
// 	file << dataValues->getLoad2I() << "\n";

// 	file << dataValues->getLoad3Off() << "\n";
	file << dataValues->getLoad3State() << "\n";
// 	file << dataValues->getLoad3U() << "\n";
// 	file << dataValues->getLoad3I() << "\n";

	file << dataValues->getCoolerOff() << "\n";
	file << dataValues->getCoolerForcedOn() << "\n";

	file << dataValues->getExitU() << "\n";

	File.close();
}
