#include "logoutput.h"

LogOutput::LogOutput(QObject *parent) : QObject(parent)
{

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
        case ServerInvalid:
            qDebug() << "ERROR: Server could not start. Make sure you are using a valid IP address and port.";
            break;
    }
}

