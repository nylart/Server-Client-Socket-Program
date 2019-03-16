#ifndef GLOBAL_H
#define GLOBAL_H

const QString DEFAULT = "default";
const QString DEFAULT_IP = "127.0.0.1";
const quint16 DEFAULT_PORT = 5000;
const quint16 ADDRESS = 1;
const quint16 PORT = 2;
const quint16 XML = 3;
const quint16 XML_DEFAULT = 2;

const QString COMMAND = "Command";

// Type of error
enum ErrorType {
    Format, Port, Address, ServerInvalid, Unconnected, FailedXML, UnexistantXML, InvalidXML, SocketWrite, SocketConnect
};


#endif // GLOBAL_H
