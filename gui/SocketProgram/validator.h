#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <QObject>
#include <QHostAddress>
#include <QCoreApplication>
#include <QXmlStreamReader>
#include <QFile>

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
    bool CheckCustomFields(QString type, QString addressField, quint64 port64);

signals:
    void updateServerText(QString message);
    void updateClientText(QString message);

protected slots:
    void WriteToUI(QString type, QString msg);

private:
};

#endif // VALIDATOR_H
