#ifndef GLOBAL_H
#define GLOBAL_H

const QString DEFAULT = "default";
const QString DEFAULT_IP = "127.0.0.1";
const quint16 DEFAULT_PORT = 5000;
const quint16 ADDRESS = 1;
const quint16 PORT = 2;

const int MAX_THREAD_COUNT = 20;

const QString COMMAND = "Command";
const QString CLIENT = "CLIENT";
const QString SERVER = "SERVER";

// Type of error
enum ErrorType {
    Format, Port, Address, ServerInvalid, UnexistantXML,InvalidXML, Schema, SocketWrite, SocketConnect
};


#endif // GLOBAL_H
