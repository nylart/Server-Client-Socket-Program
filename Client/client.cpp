#include <QFile>
#include <QXmlStreamReader>
#include "client.h"
#include "logoutput.h"


Client::Client(QObject *parent) : QObject(parent)
{
    logger.Write("Client initialized");
    socket = new QTcpSocket();
}

void Client::OpenSocket(QString ipAddress, quint16 port){
    logger.Write("Connecting to " + ipAddress + ":" + port);

    socket->connectToHost(ipAddress, port);

    if(socket->waitForConnected(3000)) {
        logger.Write("Socket waiting for connection");
        connect(socket, SIGNAL(connected()), this, SLOT(Connected()));
        connect(socket, SIGNAL(disconnected()), this, SLOT(Disconnected()));
        connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
        connect(socket, SIGNAL(bytesWritten(qint64)), this, SLOT(bytesWritten(qint64)));

    }
    else{
        logger.ThrowError(Unconnected);
        qDebug() << socket->error();
    }
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
void Client::connected() {
   logger.Write("Connected to socket.");
}

// On Disconnected
void Client::disconnected() {
    logger.Write("Disconnected from socket");
}

// Output the XML data
void Client::readyRead() {
    logger.Write(socket->readAll());
}

// On Complete
void Client::bytesWritten(qint64 bytes) {
    logger.Write("XML has successfully been sent to server");
}
