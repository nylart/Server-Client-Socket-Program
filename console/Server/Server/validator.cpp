#include "validator.h"
#include "global.h"
#include "logoutput.h"

Validator::Validator(QObject *parent) : QObject(parent)
{

}

// Purpose: Checks whether or not the passed port is valid
// Thought: This is checking whether the port falls within the range
// of a registered port, rather than a well-known port (0 to 1024) because
// system processes typically use those ports.
bool Validator::IsValidPort(quint64 port){
    if(port > 1024 && port < 655535)
        return true;
    else
        return false;
}


// Purpose: Checks whether or not the passed parameter is a valid IP address
bool Validator::IsValidIPAddress(QString ipAddress){
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
