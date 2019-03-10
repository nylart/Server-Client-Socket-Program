#ifndef CHECKVALIDITY_H
#define CHECKVALIDITY_H

#include <QObject>
#include <QDebug>
#include <QTcpServer>
#include <QTcpSocket>

class CheckValidity
{
public:
    CheckValidity();
    bool IsValidArgument(int argc, char *argv[]);
    bool IsValidIPAddress(QString ipAddress);
    bool IsValidPort(qint16 port);
};

#endif // CHECKVALIDITY_H
