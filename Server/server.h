#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QDebug>
#include <QTcpServer>
#include <QTcpSocket>
#include "logoutput.h"

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);
    void Start(QHostAddress *ipAddress, quint16 port);

signals:

public slots:
    void newConnection(qintptr  socketPtr);

protected:



private:
    QTcpServer *server;
    LogOutput logger;
};

#endif // SERVER_H
