#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <QObject>
#include <QHostAddress>

class Validator : public QObject
{
    Q_OBJECT
public:
    explicit Validator(QObject *parent = nullptr);
    bool IsValidArgument(int argc, char *argv[]);
    bool IsValidIPAddress(QString ipAddress);
    bool IsValidPort(qint16 port);

signals:

public slots:
};

#endif // VALIDATOR_H
