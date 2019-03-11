#ifndef XMLPROCESSOR_H
#define XMLPROCESSOR_H

#include <QObject>
#include <QBuffer>
#include <QRunnable>
#include <QXmlStreamReader>
#include "logoutput.h"

class XMLProcessor : public QObject,public QRunnable
{
    Q_OBJECT
public:
    XMLProcessor();
    void Run();
    void SaveXMLBytes(QByteArray byteArray);
    QString GetCommand();

signals:
    void Result(QByteArray byteArray);

private:
    QByteArray xmlByteArray;
    LogOutput logger;
};

#endif // XMLPROCESSOR_H
