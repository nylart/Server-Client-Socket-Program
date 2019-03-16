#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <QObject>
#include <QHostAddress>
#include <QCoreApplication>
#include <QXmlStreamReader>
#include <QFile>
#include "logoutput.h"

class Validator : public QObject
{
    Q_OBJECT
public:
    explicit Validator(QObject *parent = nullptr);
    bool IsValidArgument(int argc, char *argv[]);
    bool IsValidIPAddress(QString ipAddress);
    bool IsValidPort(quint64 port);
    bool IsValidXML(QString fileName);
    bool IsValidXML(QByteArray xmlBytes);

signals:

public slots:

private:
    LogOutput logger;
};

#endif // VALIDATOR_H
