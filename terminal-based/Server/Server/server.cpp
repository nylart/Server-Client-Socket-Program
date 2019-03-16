#include "server.h"
#include "receiver.h"

Server::Server()
{

}

// Purpose: Start the server and listen to the passed IP address and port.
void Server::StartServer(QString ipAddress, quint16 port) {

    // Create a QHostAddress from the default address
    QHostAddress * address = new QHostAddress(ipAddress);

    // Start the server.
    // If the server cannot connect to the passed ip address and port, show error.
    if(this->listen(*address, port)) {
        logger.Write("Server started: " + ipAddress + ":" + QString::number(port));
        if(this->isListening())
            logger.Write("Server is listening.");
    }
    else {
        logger.ThrowError(ServerInvalid);
    }
    delete address;
}

// Purpose: This is an override function for when a new connection is available and allows the
// client to connect with the server. The socketDescriptor argument is the native socket descriptor for the accepted connection.
void Server::incomingConnection(qintptr socketDescriptor) {
    // Create a new receiver that will receive the data
    Receiver *receiver = new Receiver();
    receiver->ConnectSocket(socketDescriptor);
}

