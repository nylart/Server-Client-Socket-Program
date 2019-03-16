#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include "logoutput.h"

class Server : public QTcpServer
{
    Q_OBJECT
public:
    Server();
    void StartServer(QString ipAddress, quint16 port);

protected:
    void incomingConnection(qintptr socketDescriptor);
    LogOutput logger;
};

#endif // SERVER_H
