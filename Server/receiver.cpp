#include <QThreadPool>
#include <QDate>
#include <QRunnable>
#include "receiver.h"
#include "xmlprocessor.h"


Receiver::Receiver(QObject *parent) : QObject(parent)
{
    QThreadPool::globalInstance() -> setMaxThreadCount(15);
}

// Open socket and listen for incoming data
void Receiver::ConnectSocket(int descriptor) {
    socket = new QTcpSocket(this);

    connect(socket, SIGNAL(Connected()), this, SLOT(Connected()));
    connect(socket, SIGNAL(Disconnected()), this, SLOT(Disconnected()));
    connect(socket, SIGNAL(CreateXMLProcessor()), this, SLOT(CreateXMLProcessor()));

    socket->setSocketDescriptor(descriptor);
}


void Receiver::Connected() {
    logger.Write("Receiver is connected to the socket.");
}

void Receiver::Disconnected() {
    logger.Write("Receiver is disconnected from the socket");
    deleteLater();
}

void Receiver::CreateXMLProcessor() {

    XMLProcessor *xmlProcessor;

    // Read all the the xml bytes and save it in the xml processor's byte array
    xmlProcessor->SaveXMLBytes(socket->readAll());

    //Force QThreadPool to automatically delete this runnable after calling run();
    xmlProcessor->setAutoDelete(true);

    connect(xmlProcessor, SIGNAL(Result(QByteArray)), this, SLOT(XMLComplete(QByteArray)), Qt::QueuedConnection);

    QThreadPool::globalInstance()->start(xmlProcessor);
}

void Receiver::XMLComplete(QByteArray xmlBytes) {
    socket->write(xmlBytes);
    logger.Write("Response: " + xmlBytes + QDate::currentDate().toString());
}
