#include "client.h"

Client::Client(QObject *parent) : QObject(parent)
{
    socket = new QTcpSocket();
}

// Purpose: Start the socket and connect to the passed IP Address and port
void Client::StartSocket(QString ipAddress, quint16 port) {
    logger.Write("Connecting to " + ipAddress + ":" + QString::number(port));

    socket->connectToHost(ipAddress, port);

    if(socket->waitForConnected(3000)) {
        connect(socket, SIGNAL(connected()), this, SLOT(connected()));
        connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
        connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
        connect(socket, SIGNAL(bytesWritten(qint64)), this, SLOT(bytesWritten(qint64)));
    }
    else
        logger.ThrowError(SocketConnect);
}

void Client::connected() {
   logger.Write("Connected to socket.");
}

void Client::disconnected() {
   logger.Write("Disconnected from socket");
}

// Purpose: Output the XML data.
void Client::readyRead() {
    logger.Write(socket->readAll());
}

// Purpose: Write the XML to the socket if the socket is open.
bool Client::SendXML(QByteArray xmlBytes) {
    if(socket->isOpen()) {
        socket->write(xmlBytes);
        return true;
    }
    else {
        return false;
    }
}

// Purpose: On Complete, notify that the XML sending was a success.
void Client::bytesWritten(qint64 bytes) {
    logger.Write("XML has successfully been sent to server");
}

