#ifndef LOGOUTPUT_H
#define LOGOUTPUT_H

#include <QObject>
#include <QDebug>
#include "global.h"

class LogOutput : public QObject
{
    Q_OBJECT
public:
    LogOutput();
    void ThrowError(ErrorType errorType);
    void Write(QString message);
    void WriteToUIServer(QString message);
    void WriteToUIClient(QString message);

signals:
    void SendMessageToUIClient(QString message);
    void SendMessageToUIServer(QString message);
};

#endif // LOGOUTPUT_H
