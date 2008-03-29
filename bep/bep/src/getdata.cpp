#include <QtCore>

#include "getdata.h"

GETDATA::GETDATA(DATA *DataValues, QTcpSocket *TCPSocket) : QObject() {
	dataValues = DataValues;

	timer = new QTimer(this);
//
// 	QObject::connect(timer, SIGNAL(timeout()), this, SLOT(readData()));
// 	timer->start(100);

	tcpSocket = TCPSocket;
	connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readDataN()));
	blockSize = 0;
}

// void GETDATA::setSNMPSess(netsnmp_session *SS) {
// 	ss = SS;
// }

void GETDATA::readDataN() {
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

	for (int i = 0; i < newData.split(";").size() - 1; i += 2) {
		QString parametr = newData.split(";").at(i);
		QString value = newData.split(";").at(i + 1);
		if (parametr == "LdefState") dataValues->setLdefState(value.toInt());
		if (parametr == "ACU") dataValues->setACU(value.toFloat());
		if (parametr == "KNS1Off") dataValues->setKNSOff(1, value.toInt());
		if (parametr == "KNS1Avar") dataValues->setKNSAvar(1, value.toInt());
		if (parametr == "KNS1Avarseti") dataValues->setKNSAvarseti(1, value.toInt());
		if (parametr == "KNS1Ogran") dataValues->setKNSOgran(1, value.toInt());
		if (parametr == "KNS1Peregrev") dataValues->setKNSPeregrev(1, value.toInt());
		if (parametr == "KNS1Temp") dataValues->setKNSTemp(1, value.toFloat());
		if (parametr == "KNS2Off") dataValues->setKNSOff(2, value.toInt());
		if (parametr == "KNS2Avar") dataValues->setKNSAvar(2, value.toInt());
		if (parametr == "KNS2Avarseti") dataValues->setKNSAvarseti(2, value.toInt());
		if (parametr == "KNS2Ogran") dataValues->setKNSOgran(2, value.toInt());
		if (parametr == "KNS2Peregrev") dataValues->setKNSPeregrev(2, value.toInt());
		if (parametr == "KNS2Temp") dataValues->setKNSTemp(2, value.toFloat());
		if (parametr == "KNS3Off") dataValues->setKNSOff(3, value.toInt());
		if (parametr == "KNS3Avar") dataValues->setKNSAvar(3, value.toInt());
		if (parametr == "KNS3Avarseti") dataValues->setKNSAvarseti(3, value.toInt());
		if (parametr == "KNS3Ogran") dataValues->setKNSOgran(3, value.toInt());
		if (parametr == "KNS3Peregrev") dataValues->setKNSPeregrev(3, value.toInt());
		if (parametr == "KNS3Temp") dataValues->setKNSTemp(3, value.toFloat());
		if (parametr == "KNS4Off") dataValues->setKNSOff(4, value.toInt());
		if (parametr == "KNS4Avar") dataValues->setKNSAvar(4, value.toInt());
		if (parametr == "KNS4Avarseti") dataValues->setKNSAvarseti(4, value.toInt());
		if (parametr == "KNS4Ogran") dataValues->setKNSOgran(4, value.toInt());
		if (parametr == "KNS4Peregrev") dataValues->setKNSPeregrev(4, value.toInt());
		if (parametr == "KNS4Temp") dataValues->setKNSTemp(4, value.toFloat());
		if (parametr == "AKB1Off") dataValues->setAKBOff(1, value.toInt());
		if (parametr == "AKB1U1") dataValues->setAKBU1(1, value.toFloat());
		if (parametr == "AKB1U2") dataValues->setAKBU2(1, value.toFloat());
		if (parametr == "AKB1U3") dataValues->setAKBU3(1, value.toFloat());
		if (parametr == "AKB1U4") dataValues->setAKBU4(1, value.toFloat());
		if (parametr == "AKB1U5") dataValues->setAKBU5(1, value.toFloat());
		if (parametr == "AKB1I") dataValues->setAKBI(1, value.toFloat());
		if (parametr == "AKB1Temp") dataValues->setAKBTemp(1, value.toFloat());
		if (parametr == "AKB2Off") dataValues->setAKBOff(2, value.toInt());
		if (parametr == "AKB2U1") dataValues->setAKBU1(2, value.toFloat());
		if (parametr == "AKB2U2") dataValues->setAKBU2(2, value.toFloat());
		if (parametr == "AKB2U3") dataValues->setAKBU3(2, value.toFloat());
		if (parametr == "AKB2U4") dataValues->setAKBU4(2, value.toFloat());
		if (parametr == "AKB2U5") dataValues->setAKBU5(2, value.toFloat());
		if (parametr == "AKB2I") dataValues->setAKBI(2, value.toFloat());
		if (parametr == "AKB2Temp") dataValues->setAKBTemp(2, value.toFloat());
		if (parametr == "LoadOff") dataValues->setLoadOff(value.toInt());
		if (parametr == "LoadI") dataValues->setLoadI(value.toFloat());
		if (parametr == "Load1State") dataValues->setLoad1State(value.toInt());
		if (parametr == "Load2State") dataValues->setLoad2State(value.toInt());
		if (parametr == "Load3State") dataValues->setLoad3State(value.toInt());
		if (parametr == "CoolerOff") dataValues->setCoolerOff(value.toInt());
		if (parametr == "CoolerForcedOn") dataValues->setCoolerForcedOn(value.toInt());
		if (parametr == "ExitU") dataValues->setExitU(value.toFloat());
	}
	blockSize = 0;

// 	netsnmp_pdu *pdu;
// 	netsnmp_pdu *response;
//
// 	oid anOID[MAX_OID_LEN];
// 	size_t anOID_len;
//
// 	netsnmp_variable_list *vars;
// 	int status;
// 	int count = 1;
//
//
// 	/*
// 	* Create the PDU for the data for our request.
// 	*   1) We're going to GET the system.sysDescr.0 node.
// 	*/
// 	pdu = snmp_pdu_create(SNMP_MSG_GET);
// 	anOID_len = MAX_OID_LEN;
// 	if (!snmp_parse_oid(".1.3.6.1.2.1.1.1.0", anOID, &anOID_len)) {
// 		snmp_perror(".1.3.6.1.2.1.1.1.0");
// 		SOCK_CLEANUP;
// 		exit(1);
// 	}
// #if OTHER_METHODS
// 	/*
// 	*  These are alternatives to the 'snmp_parse_oid' call above,
// 	*    e.g. specifying the OID by name rather than numerically.
// 	*/
// 	read_objid(".1.3.6.1.2.1.1.1.0", anOID, &anOID_len);
// 	get_node("sysDescr.0", anOID, &anOID_len);
// 	read_objid("system.sysDescr.0", anOID, &anOID_len);
// #endif
//
// 	snmp_add_null_var(pdu, anOID, anOID_len);
//
// 	/*
// 	* Send the Request out.
// 	*/
// 	status = snmp_synch_response(ss, pdu, &response);
//
// 	/*
// 	* Process the response.
// 	*/
// 	if (status == STAT_SUCCESS && response->errstat == SNMP_ERR_NOERROR) {
// 		/*
// 		* SUCCESS: Print the result variables
// 		*/
//
// 		for (vars = response->variables; vars; vars = vars->next_variable)
// 			print_variable(vars->name, vars->name_length, vars);
//
// 		/* manipuate the information ourselves */
// 		for (vars = response->variables; vars; vars = vars->next_variable) {
// 			if (vars->type == ASN_OCTET_STR) {
// 				char *sp = (char *)malloc(1 + vars->val_len);
// 				memcpy(sp, vars->val.string, vars->val_len);
// 				sp[vars->val_len] = '\0';
// 				printf("value #%d is a string: %s\n", count++, sp);
// 				free(sp);
// 			} else
// 				printf("value #%d is NOT a string! Ack!\n", count++);
// 		}
// 	} else {
// 		/*
// 		* FAILURE: print what went wrong!
// 		*/
//
// 		if (status == STAT_SUCCESS)
// 			fprintf(stderr, "Error in packet\nReason: %s\n",
// 			        snmp_errstring(response->errstat));
// 		else if (status == STAT_TIMEOUT)
// 			fprintf(stderr, "Timeout: No response from server.\n");
// 		else
// 			snmp_sess_perror("snmpdemoapp", ss);
//
// 	}
//
// 	if (response)
// 		snmp_free_pdu(response);
}

void GETDATA::readDataF() {
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
}
