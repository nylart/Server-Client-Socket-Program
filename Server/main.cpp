#include <QCoreApplication>
#include "global.h"
#include "server.h"
#include "validator.h"
#include "logoutput.h"

// Start the server with the default address and port.
void StartDefaultServer(){

    qDebug() << "StartDefaultServer";
    // Start the server
    Server server;
    server.StartServer(DEFAULTIP, DEFAULTPORT);
}

// Start the server with the passed address and port.
void StartServer(char *argAddress, char *argPort){
    qDebug() << "StartServer";
    // Convert the passed address and port to QString and qint16
    QString address = argAddress;
    qint16 portInt = atoi(argPort);


    // Start the server
    Server server;
    server.StartServer(address, portInt);
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Validator validator;
    LogOutput logger;
    switch(argc){
        case 2:
            // Check if the command line arguments are valid
            if(validator.IsValidArgument(argc, argv)){
                // Try to start the default server.
                StartDefaultServer();
            }
            else
                // Argument was not default, throw an error.
                logger.ThrowError(Format);
            return 0;
            break;
        case 3:
            // Check if the command line arguments are valid
            if(validator.IsValidArgument(argc, argv)){
                // Try to start a server with passed ip address and port
                StartServer(argv[ADDRESS], argv[PORT]);
            }
            else
                // Argument was not default, throw an error.
                logger.ThrowError(Format);
            return 0;
            break;
        default:
            // Not the right number of command line arguments.
            logger.ThrowError(Format);
            return 0;
            break;

    }

    return a.exec();
}
