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
    bool IsValidIPAddress(QString ipAddress);
    bool IsValidPort(quint64 port);

signals:

public slots:

private:
    LogOutput logger;
};

#endif // VALIDATOR_H
