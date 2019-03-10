#include <QFile>
#include <QXmlStreamReader>
#include "client.h"
#include "logoutput.h"


Client::Client(QObject *parent) : QObject(parent)
{
    socket = new QTcpSocket();
}

void Client::OpenSocket(QString ipAddress, quint16 port){
    logger.Write("Connecting to " + ipAddress + ":" + port);

    socket->connectToHost(ipAddress, port);

    if(socket->waitForConnected(WAIT_TIME)) {

        connect(socket, SIGNAL(Connected()), this, SLOT(Connected()));
        connect(socket, SIGNAL(Disconnected()), this, SLOT(Disconnected()));
        connect(socket, SIGNAL(OutputXML()), this, SLOT(OutputXML()));
        connect(socket, SIGNAL(SendXMLComplete(qint64)), this, SLOT(SendXMLComplete(qint64)));

    }
    else
        logger.ThrowError(Unconnected);
}

// Write the XML to the socket if the socket is open
bool Client::SendXML(QByteArray xmlBytes){
    if(socket->isOpen()) {
        socket->write(xmlBytes);
        return true;
    }
    else {
        return false;
    }
}

// On Connected
void Client::Connected() {
   logger.Write("Connected to socket.");
}

// On Disconnected
void Client::Disconnected() {
    logger.Write("Disconnected from socket");
}

// Output the XML data
void Client::OutputXML() {
    logger.Write(socket->readAll());
}

// On Complete
void Client::SendXMLComplete(qint64 bytes) {
    logger.Write("XML has successfully been sent to server");
}
