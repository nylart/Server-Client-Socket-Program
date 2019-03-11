#include "server.h"
#include "global.h"
#include "logoutput.h"
#include "receiver.h"

Server::Server(QObject *parent) : QObject(parent)
{

}

// Start the server and listen to the passed IP address and port.
void Server::Start(QHostAddress *ipAddress, quint16 port){
    server = new QTcpServer(this);
    LogOutput logger;
    // Connect signals and slots with newConnection().
    // This way we know when client connects to server.
    //connect(server, SIGNAL(newConnection()), server, SLOT(newConnection()));

    // Start the server.
    // If the server cannot connect to the passed ip address and port, show error.
    if(!server->listen(*ipAddress, port)){
        logger.ThrowError(ServerInvalid);
    }
    else {
        qDebug() << "Server started.";
    }
}


//
void Server::newConnection(qintptr  socketPtr){
    Receiver receiver;
    receiver.ConnectSocket(socketPtr);
    logger.Write("New socket connected");
}
