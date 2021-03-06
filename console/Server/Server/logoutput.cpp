#include "logoutput.h"

LogOutput::LogOutput(QObject *parent) : QObject(parent)
{

}

// Purpose: Output the passed message
//
// Thought: I know I could've just used qDebug() << "Message"; whenever I wanted
// to write output, but I thought that consistently writing the message to the LogOutput object
// would be more consistent. I also used .noquote() in order to ignore special characters such as
// linefeeds when outputting the message. This is particularly helpful when writing out the output XML response
void LogOutput::Write(QString message){
    qDebug().noquote() << message;
}

// Purpose: Throw an error message dependent on error type
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
            qDebug() << "ERROR: Invalid port.";
            break;
        case Address:
            qDebug() << "ERROR: Invalid IP address.";
            break;
        case ServerInvalid:
            qDebug() << "ERROR: Server could not start. Make sure you are using a valid IP address and port.";
            break;
        case UnexistantXML:
            qDebug() << "ERROR: XML does not exist.";
        case InvalidXML:
            qDebug() << "ERROR: The file is invalid. Must be a non-empty XML.";
        case Schema:
            qDebug() << "ERROR: Missing Schema.";
        default:
            break;
    }
}

