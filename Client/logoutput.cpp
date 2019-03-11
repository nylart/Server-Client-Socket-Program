#include "logoutput.h"

LogOutput::LogOutput(QObject *parent) : QObject(parent)
{

}

// Output the passed message
void LogOutput::Write(QString message){
    qDebug() << message;
}

// Throw an error message dependent on error type
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
        case XMLInvalid:
            qDebug() << "ERROR: Invalid XML file";
            break;
        case UnexistantXML:
            qDebug() << "ERROR: XML does not exist";
        default:
            break;
    }
}
