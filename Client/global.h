#ifndef GLOBAL_H
#define GLOBAL_H

const QString DEFAULT = "default";
const QString DEFAULTIP = "127.0.0.1";
const quint16 DEFAULTPORT = 5000;
const quint16 ADDRESS = 1;
const quint16 PORT = 2;
const quint16 XML = 3;
const quint16 XML_DEFAULT = 2;
const quint16 WAIT_TIME = 3000;

// Type of error
enum ErrorType {
    Format, Port, Address, ServerInvalid, XMLInvalid, Unconnected, FailedXML
};

#endif // GLOBAL_H
