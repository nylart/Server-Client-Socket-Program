#include "receiver.h"
#include "xmlprocessor.h"
#include "global.h"

Receiver::Receiver(QObject *parent) : QObject(parent)
{
    // Set the amount of maximum threads allowed to be used by the thread pool
    QThreadPool::globalInstance() -> setMaxThreadCount(MAX_THREAD_COUNT);
}

// Purpose: Open socket and listen for incoming data
void Receiver::ConnectSocket(int socketDescriptor) {
    socket = new QTcpSocket(this);

    connect(socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));

    // Initialize the socket with the native socket descriptor
    socket->setSocketDescriptor(socketDescriptor);
}

// Purpose: This signal is emitted after connectToHost() has been called and a connection has been successfully established.
void Receiver::connected() {
    logger.WriteToUIServer("Receiver is connected to the socket.");
}

// Purpose: This signal is emitted when the socket has been disconnected. We should also
// delete this Receiver object since it is no longer being used.
//
// Thought: I thought it'd be best to delete the object here when we know that it was disconnected.
// Additionally, by using deleteLater() it will be safe if this signal happened to occur more than once.
void Receiver::disconnected() {
    logger.Write("Receiver is disconnected from the socket");
    deleteLater();
}

// Purpose: When the signal lets us know there's new data available, read from the device
//
// Thought: I decided to use the Thread Pool so QT can manage the collection of threads
// and maintain the thread objects. There will be no race conditions, because we instantiate
// a new XMLProcessor object each time.
void Receiver::readyRead() {
    // Create the xml processor
    XMLProcessor *xmlProcessor = new XMLProcessor();

    // Read all the the xml bytes and save it in the xml processor's byte array
    QByteArray xmlBytes = socket->readAll();
    xmlProcessor->SaveXMLBytes(xmlBytes);

    //Force QThreadPool to automatically delete this runnable after calling run();
    xmlProcessor->setAutoDelete(true);

    connect(xmlProcessor, SIGNAL(Result(QByteArray)), this, SLOT(XMLComplete(QByteArray)), Qt::QueuedConnection);

    // Instantiate an xml processor
    QThreadPool::globalInstance()->start(xmlProcessor);
}

// Purpose: When the reading of the xml has completed, write the number of bytes written to the device
// and output the response to an output file and to the stream
//
// Thought: For the output of the data, I thought it'd be easier to use the QDomDocument to create
// the output XML data with more ease.
void Receiver::XMLComplete(QByteArray commands) {
    // write the number of bytes written to the device
    socket->write(commands);


    // Create an output file of the data sent
    QFile file("OutputXML.xml");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        file.close();
        logger.WriteToUIServer("Cannot open file for writing");
        return;
    }

    // Create a document that will hold the response xml data
    QDomDocument document;

    QDomProcessingInstruction process = document.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"UTF-8\"");
    document.appendChild(process);

    // Add the root element: response
    QDomElement rootElement = document.createElement("response");
    document.appendChild(rootElement);

    // Add the command tag and the actual command text
    QDomElement command = document.createElement("command");
    QDomText commandText = document.createTextNode(commands);
    command.appendChild(commandText);
    rootElement.appendChild(command);

    // Add the status tag and the status
    QDomElement status = document.createElement("status");
    QDomText statusText;
    // If the command is unknown, then have status as Incomplete
    if(commands == "Unknown Command"){
        statusText = document.createTextNode("Incomplete");
    }
    else
        statusText = document.createTextNode("Complete");
    status.appendChild(statusText);
    rootElement.appendChild(status);

    // Add the date tag and the date
    QDomElement date = document.createElement("date");
    QDomText dateText = document.createTextNode(QDate::currentDate().toString());
    date.appendChild(dateText);
    rootElement.appendChild(date);

    // Write the data out to the file
    QTextStream out(&file);
    out << document.toString();

    // Parse the command and display it to the console along with any data rows
    logger.WriteToUIServer("=== Received ===");
    logger.WriteToUIServer(document.toString());
    logger.WriteToUIServer("=== End Received ===");
}
