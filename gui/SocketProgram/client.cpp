#include "client.h"
#include "global.h"

Client::Client(QObject *parent) : QObject(parent)
{
    socket = new QTcpSocket();
}

// Purpose: Start the socket and connect to the passed IP Address and port
void Client::StartSocket(QString ipAddress, quint16 port) {
    WriteToUI("Connecting to " + ipAddress + ":" + QString::number(port));

    socket->connectToHost(ipAddress, port);

    if(socket->waitForConnected(3000)) {
        connect(socket, SIGNAL(connected()), this, SLOT(connected()));
        connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
        connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
        connect(socket, SIGNAL(bytesWritten(qint64)), this, SLOT(bytesWritten(qint64)));
    }
    else
        WriteToUI(SOCKET_CONNECTION_ERROR);
}

// Purpose: Emit the passed message to the UI's Client text area
void Client::WriteToUI(QString msg){
    emit updateClientText(msg);
}

void Client::connected() {
   WriteToUI("Connected to socket.");
}

void Client::disconnected() {
   WriteToUI("Disconnected from socket");
}

// Purpose: Output the XML data.
void Client::readyRead() {
    WriteToUI(socket->readAll());
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
    WriteToUI("XML has successfully been sent to server");
}

