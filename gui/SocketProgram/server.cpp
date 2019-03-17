#include "server.h"
#include "receiver.h"
#include "global.h"

Server::Server()
{

}

// Purpose: Start the server and listen to the passed IP address and port.
void Server::StartServer(QString ipAddress, quint16 port) {

    // Create a QHostAddress from the default address
    QHostAddress *address = new QHostAddress(ipAddress);

    // Start the server.
    // If the server cannot connect to the passed ip address and port, show error.
    if(this->listen(*address, port)) {
        WriteToUI("Server started: " + ipAddress + ":" + QString::number(port));
        WriteToUI("Server is listening.");
    }
    else {
        WriteToUI(SERVER_INVALID_ERROR);
    }
    delete address;
}

// Purpose: Emit a signal that will update the UI's Server Text area to display the message
void Server::WriteToUI(QString msg){
    emit updateServerText(msg);
}

// Purpose: This is an override function for when a new connection is available and allows the
// client to connect with the server. The socketDescriptor argument is the native socket descriptor for the accepted connection.
void Server::incomingConnection(qintptr socketDescriptor) {
    // Create a new receiver that will receive the data
    Receiver *receiver = new Receiver();
    connect(receiver, SIGNAL(updateServerText(QString)), this, SLOT(WriteToUI(QString)));
    receiver->ConnectSocket(socketDescriptor);
}

