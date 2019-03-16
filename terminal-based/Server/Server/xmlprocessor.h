#ifndef XMLPROCESSOR_H
#define XMLPROCESSOR_H

#include <QRunnable>
#include <QObject>
#include <QXmlSchema>
#include <QXmlSchemaValidator>
#include <QXmlStreamReader>
#include <QDebug>
#include <QBuffer>
#include "logoutput.h"

class XMLProcessor : public QObject, public QRunnable
{
    Q_OBJECT
public:
    XMLProcessor();
    void run();
    void SaveXMLBytes(QByteArray xmlBytes);
    QString GetCommand();
    bool IsValidXML();

signals:
    void Result(QByteArray byteArray);

private:
    // holds the xml
    QByteArray xmlByteArray;

    LogOutput logger;

};

#endif // XMLPROCESSOR_H
