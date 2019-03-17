#ifndef XMLPROCESSOR_H
#define XMLPROCESSOR_H

#include <QRunnable>
#include <QObject>
#include <QXmlSchema>
#include <QXmlSchemaValidator>
#include <QXmlStreamReader>
#include <QDebug>
#include <QBuffer>

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
    void updateServerText(QString message);

protected:
    void WriteToUI(QString msg);

private:
    // holds the xml
    QByteArray xmlByteArray;

};

#endif // XMLPROCESSOR_H
