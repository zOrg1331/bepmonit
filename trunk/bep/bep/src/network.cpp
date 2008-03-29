#include "network.h"

network::network(QTcpSocket *TcpSocket, log *Logger, conf *Conf, GETDATA *GetData) : QObject() {
	logger = Logger;
	tcpSocket = TcpSocket;
	confer = Conf;
	getData = GetData;

	stunn = new stunnel(confer);
	connect(stunn, SIGNAL(succStarted()), this, SLOT(connectToDevice()));

	connect(tcpSocket, SIGNAL(connected()), this, SLOT(connectionEst()));
	connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
			this, SLOT(displayError(QAbstractSocket::SocketError)));

	connect(confer, SIGNAL(confChanged()), this, SLOT(reconnect()));
}

network::~network() {

}

void network::closeConnection() {
	if (stunn->running()) {
		stunn->closeStunnel();
	}
}

void network::reconnect() {
	if (stunn->running()) {
		stunn->closeStunnel();
		stunn->setupStunnel();
	}
}

void network::estConnection() {
	if (!stunn->running()) {
 		stunn->setupStunnel();
	} else {
		connectToDevice();
	}
}

void network::connectToDevice() {
	tcpSocket->abort();
	tcpSocket->connectToHost("127.0.0.1", 12354);

// 	const char *our_v3_passphrase = "1234567890";
// 	netsnmp_session session, *ss;
//
// 	/*
// 	* Initialize the SNMP library
// 	*/
// 	init_snmp("snmpdemoapp");
//
// 	/*
// 	* Initialize a "session" that defines who we're going to talk to
// 	*/
// 	snmp_sess_init(&session);                     /* set up defaults */
// 	session.peername = strdup("192.168.0.221");
//
// 	/* set up the authentication parameters for talking to the server */
//
// 	/* Use SNMPv3 to talk to the experimental server */
//
// 	/* set the SNMP version number */
// 	session.version = SNMP_VERSION_3;
//
// 	/* set the SNMPv3 user name */
// 	session.securityName = strdup("user");
// 	session.securityNameLen = strlen(session.securityName);
//
// 	/* set the security level to authenticated, but not encrypted */
// 	session.securityLevel = SNMP_SEC_LEVEL_AUTHNOPRIV;
//
// 	/* set the authentication method to MD5 */
// 	session.securityAuthProto = usmHMACMD5AuthProtocol;
// 	session.securityAuthProtoLen = sizeof(usmHMACMD5AuthProtocol) / sizeof(oid);
// 	session.securityAuthKeyLen = USM_AUTH_KU_LEN;
//
// 	/* set the authentication key to a MD5 hashed version of our
// 	passphrase "The Net-SNMP Demo Password" (which must be at least 8
// 	characters long) */
// 	if (generate_Ku(session.securityAuthProto,
// 	                session.securityAuthProtoLen,
// 	                (u_char *) our_v3_passphrase, strlen(our_v3_passphrase),
// 	                session.securityAuthKey,
// 	                &session.securityAuthKeyLen) != SNMPERR_SUCCESS) {
// 		snmp_perror("bep");
// 		snmp_log(LOG_ERR, "Error generating Ku from authentication pass phrase. \n");
// 		exit(1);
// 	}
//
// 	/*
// 	 * Open the session
// 	 */
// 	SOCK_STARTUP;
// 	ss = snmp_open(&session);                     /* establish the session */
//
// 	if (!ss) {
// 		snmp_sess_perror("ack", &session);
// 		SOCK_CLEANUP;
// 		exit(1);
// 	}
//
// 	getData->setSNMPSess(ss);

// 	snmp_close(ss);

// 	SOCK_CLEANUP;
}

void network::connectionEst() {
	logger->setMsg(4, 0, "приложение;соединение;1");
}

void network::displayError(QAbstractSocket::SocketError socketError)
{
	QMessageBox msgBox;
	msgBox.setStandardButtons(QMessageBox::Ok);
	msgBox.setText(trUtf8("Не удается установить соединение, произошла следующая ошибка: %1").arg(tcpSocket->errorString()));
	msgBox.setWindowTitle(trUtf8("Ошибка при создании соединения"));
	msgBox.exec();
}
