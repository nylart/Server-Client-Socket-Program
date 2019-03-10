#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include "logoutput.h"

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr);
    void OpenSocket(QString ipAddress, quint16 port);
    bool SendXML(QByteArray xmlBytes);

signals:

public slots:
    void Connected();
    void Disconnected();
    void OutputXML();
    void SendXMLComplete(qint64 bytes);

private:
    QTcpSocket * socket;
    LogOutput logger;
};

#endif // CLIENT_H
