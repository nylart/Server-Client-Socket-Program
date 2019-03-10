#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <QObject>
#include <QFile>
#include <QHostAddress>
#include "logoutput.h"

class Validator : public QObject
{
    Q_OBJECT
public:
    explicit Validator(QObject *parent = nullptr);
    bool IsValidArgument(int argc, char *argv[]);
    bool IsValidIPAddress(QString ipAddress);
    bool IsValidPort(qint16 port);
    bool IsValidXML(QString fileName);

signals:

public slots:

private:
    LogOutput logger;
};

#endif // VALIDATOR_H
