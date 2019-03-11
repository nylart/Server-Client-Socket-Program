#ifndef RECEIVER_H
#define RECEIVER_H

#include <QObject>
#include <QTcpSocket>
#include "logoutput.h"

class Receiver : public QObject
{
    Q_OBJECT
public:
    explicit Receiver(QObject *parent = nullptr);
    void ConnectSocket(int socketNum);

signals:

public slots:
    void Connected();
    void Disconnected();
    void CreateXMLProcessor();
    void XMLComplete(QByteArray xmlBytes);

private:
    QTcpSocket *socket;
    LogOutput logger;
};

#endif // RECEIVER_H
