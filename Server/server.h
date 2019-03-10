#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QDebug>
#include <QTcpServer>
#include <QTcpSocket>

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);
    void Start(QHostAddress *ipAddress, quint16 port);

signals:

public slots:

protected:



private:
    QTcpServer *server;
};

#endif // SERVER_H
