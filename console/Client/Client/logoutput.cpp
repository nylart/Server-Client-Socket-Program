#include "logoutput.h"
#include "global.h"

LogOutput::LogOutput(QObject *parent) : QObject(parent)
{

}

// Purpose: Output the passed message.
//
// Thought: I know I could've just used qDebug() << "Message"; whenever I wanted
// to write output, but I thought that consistently writing the message to the LogOutput object
// would be more consistent. I also used .noquote() in order to ignore special characters such as
// linefeeds when outputting the message. This is particularly helpful when writing out the output XML response
void LogOutput::Write(QString message){
    qDebug().noquote() << message;
}

// Purpose: Throw an error message dependent on error type.
//
// Thought: I wanted to manage my errors in one place since they're typically used several times.
// I could easily just change the message in one place (here) if necessary instead of having to fix
// it everywhere.
void LogOutput::ThrowError(ErrorType errorType){
    switch(errorType){
        case Format:
            qDebug() << "ERROR: Expecting format: ./main <ADDRESS> <PORT> or ./main default";
            break;
        case Port:
            qDebug() << "ERROR: Invalid port and/or IP address.";
            break;
        case Address:
            qDebug() << "ERROR: Invalid IP address.";
            break;
        case Unconnected:
            qDebug() << "ERROR: The given IP address and port are not connected";
            break;
        case FailedXML:
            qDebug() << "ERROR: The XML failed to send.";
            break;
        case InvalidXML:
            qDebug() << "ERROR: Invalid XML file";
            break;
        case UnexistantXML:
            qDebug() << "ERROR: XML does not exist";
            break;
        case SocketWrite:
            qDebug() << "ERROR: Cannot write xml to the socket";
            break;
        case SocketConnect:
            qDebug() << "ERROR: Cannot connect to the socket";
            break;
        default:
            break;
    }
}

