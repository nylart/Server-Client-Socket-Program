#ifndef LOGOUTPUT_H
#define LOGOUTPUT_H

#include <QObject>
#include <QDebug>
#include "global.h"

class LogOutput : public QObject
{
    Q_OBJECT
public:
    explicit LogOutput(QObject *parent = nullptr);
    void ThrowError(ErrorType errorType);
signals:

public slots:
};

#endif // LOGOUTPUT_H
