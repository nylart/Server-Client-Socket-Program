#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>

class Server : public QTcpServer
{
    Q_OBJECT
public:
    Server();
    void StartServer(QString ipAddress, quint16 port);

signals:
    void updateServerText(QString message);

protected slots:
        void WriteToUI(QString msg);

protected:
    void incomingConnection(qintptr socketDescriptor);

};

#endif // SERVER_H
