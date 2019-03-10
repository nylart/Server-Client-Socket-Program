#include <QCoreApplication>
#include "checkvalidity.h"
#include "global.h"
#include "errorlogger.h"

CheckValidity::CheckValidity()
{

}

// Check if the passed arguments are expected.
bool CheckValidity::IsValidArgument(int argc, char *argv[]){
    ErrorLogger errorLogger;
    if(argc == 2){
        if(QString(argv[ADDRESS]) == DEFAULT){
            return true;
        }
    }
    else if (argc == 3){
        // if the address is a valid ip, then proceed with checking port
        QString address = argv[ADDRESS];
        qint16 port = atoi(argv[PORT]);
        if(IsValidIPAddress(address)){
            if(IsValidPort(port)){
                return true;
            }
            else
                errorLogger.ThrowError(Port);
        }
        else
            errorLogger.ThrowError(Address);
    }
    errorLogger.ThrowError(Format);
    return false;
}

// Checks whether or not the passed port is valid
bool CheckValidity::IsValidPort(qint16 port){
    // Port must be within 1025 and 65534.
    if(port > 1024 && port < 655535){
        return true;
    }
    else{
        return false;
    }
}

// Checks whether or not the passed parameter is a valid ip address
bool CheckValidity::IsValidIPAddress(QString ipAddress){
    QHostAddress address(ipAddress);
    if (QAbstractSocket::IPv4Protocol == address.protocol() ||
        QAbstractSocket::IPv6Protocol == address.protocol())
    {
       return true;
    }
    else
    {
       return false;
    }
}
