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

// Errors
const QString SERVER_INVALID_ERROR = "ERROR: Server could not start. Make sure you are using a valid IP address and port.";
const QString INVALID_XML_ERROR = "ERROR: The file is invalid. Must be a non-empty XML.";
const QString SCHEMA_ERROR = "ERROR: Missing Schema.";
const QString SOCKET_CONNECTION_ERROR = "ERROR: Cannot connect to the socket";
const QString SOCKET_WRITE_ERROR = "ERROR: Cannot write xml to the socket";
const QString INVALID_ADDRESS_ERROR ="ERROR: Invalid IP address.";
const QString INVALID_PORT_ERROR = "ERROR: Invalid port.";


#endif // GLOBAL_H
