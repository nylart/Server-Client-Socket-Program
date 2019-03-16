#ifndef RECEIVER_H
#define RECEIVER_H

#include <QObject>
#include <QTcpSocket>
#include <QThreadPool>
#include <QDate>
#include <QRunnable>
#include <QDomDocument>
#include <QTextStream>
#include <QFile>

#include "logoutput.h"

class Receiver : public QObject
{
    Q_OBJECT
public:
    explicit Receiver(QObject *parent = nullptr);
    void ConnectSocket(int socketDescriptor);

signals:

public slots:
    void connected();
    void disconnected();
    void readyRead();
    void XMLComplete(QByteArray commands);

private:
    QTcpSocket *socket;
    LogOutput logger;
};

#endif // RECEIVER_H
