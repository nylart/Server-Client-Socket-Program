#include <QCoreApplication>
#include "server.h"
#include "validator.h"
#include "logoutput.h"
#include "global.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Create the server
    Server server;

    // Logger will be used to write output or throw errors
    LogOutput logger;

    // Validator that is used to check arguments passed
    Validator validator;

    // QString that will store user given IP address
    QString ipAddress;

    // Ports of 64-bit and 16-bit
    quint64 port64;
    quint16 port16;


    switch(argc){
            case 2:
                // Check if the commandline argument is "default"
                if(QString(argv[1]) == DEFAULT){
                    // Try to start the default server.
                    server.StartServer(DEFAULT_IP, DEFAULT_PORT);
                }
                else{
                    // Argument was not default, throw an error.
                    logger.ThrowError(Format);
                    return 0;
                }
            break;
            case 3:
                // Store passed arguments for ease of use
                ipAddress = QString(argv[ADDRESS]);
                port64 = QString(argv[PORT]).toLongLong();

                // Check if the IP Address passed is valid
                if(validator.IsValidIPAddress(ipAddress)){

                    // Check if the port passed is valid
                    if(validator.IsValidPort(port64)){

                        // Cast port16 to be a 16-bit uint
                        port16 = quint16(port64);

                        // Try to start a server with passed ip address and port
                        server.StartServer(ipAddress, port16);
                    }
                    else{
                        // Port was invalid, throw an error
                        logger.ThrowError(Port);
                        return 0;
                    }
                }
                else{
                    // Argument was not valid format, throw an error.
                    logger.ThrowError(Address);
                    return 0;
                }
                break;

            default:
                // Not the right number of command line arguments.
                logger.ThrowError(Format);
                return 0;
    }
    return a.exec();
}
