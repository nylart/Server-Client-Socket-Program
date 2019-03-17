#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = 0);
    void StartSocket(QString ipAddress, quint16 port);
    bool SendXML(QByteArray xmlBytes);
    bool IsSocketConnected();

signals:
    void updateClientText(QString message);

public slots:
    void connected();
    void disconnected();
    void readyRead();
    void bytesWritten(qint64 bytes);

protected:
    void WriteToUI(QString msg);

private:
    QTcpSocket *socket;
    bool isConnected;

};

#endif // CLIENT_H
