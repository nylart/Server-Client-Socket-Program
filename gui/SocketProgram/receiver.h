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
class Receiver : public QObject
{
    Q_OBJECT
public:
    explicit Receiver(QObject *parent = nullptr);
    void ConnectSocket(int socketDescriptor);

signals:
    void updateServerText(QString message);

public slots:
    void connected();
    void disconnected();
    void readyRead();
    void XMLComplete(QByteArray commands);

protected:
    void WriteToUI(QString msg);

private:
    QTcpSocket *socket;
};

#endif // RECEIVER_H
