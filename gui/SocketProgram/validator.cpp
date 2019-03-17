#include "validator.h"
#include "global.h"

Validator::Validator(QObject *parent) : QObject(parent)
{

}

// Purpose: Emit a signal that will update the UI's Server Text area to display the message
void Validator::WriteToUI(QString type, QString msg){
    if(type == SERVER)
        emit updateServerText(msg);
    else if (type == CLIENT)
        emit updateClientText(msg);
}


bool Validator::CheckCustomFields(QString type, QString addressField, quint64 port64){

    // If the text is empty or not valid, throw error
    if(addressField.isEmpty() || !IsValidIPAddress(addressField)){
        if(type == SERVER)
            WriteToUI(SERVER, INVALID_ADDRESS_ERROR);
        else if (type == CLIENT)
            WriteToUI(CLIENT, INVALID_ADDRESS_ERROR);

        return false;
    }

    // If the port is invalid, throw an error.
    if(!IsValidPort(port64)){
        if(type == SERVER)
            WriteToUI(SERVER, INVALID_PORT_ERROR);
        else if (type == CLIENT)
            WriteToUI(CLIENT, INVALID_PORT_ERROR);

        return false;
    }

    // If we made it this far, then allow the program to try to start the server next
    return true;
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
