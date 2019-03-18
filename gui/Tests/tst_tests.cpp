#include <QtTest>
#include <QTest>
#include <QCoreApplication>
#include "server.h"
#include "global.h"
#include "client.h"
#include "validator.h"
#include "xmlprocessor.h"

class Tests : public QObject
{
    Q_OBJECT

public:
    Tests();
    ~Tests();

private slots:
    void StartServer_Default_Case();
    void StartServer_Custom_Case();
    void StartClient_Default_Case();
    void StartClient_Custom_Case();
    void StartClientWithoutServer_Default_Case();
    void StartClientWithoutServer_Custom_Case();
    void InvalidAddressCase();
    void InvalidPortCase();
    void InvalidXMLFormat_Case();
    void ValidXMLFormat_Case();
    void SendXML();
    void ParseKnownCommand();
    void ParseUnknownCommand();


private:

};

Tests::Tests()
{
}

Tests::~Tests()
{

}

// Purpose: Start the server with a default IP address and port.
void Tests::StartServer_Default_Case()
{
    Server server;
    server.StartServer(DEFAULT_IP, DEFAULT_PORT);
    QVERIFY2(server.isListening(), "Server could not start for default IP address and port");
}

// Purpose: Start the server with a custom IP address and port.
void Tests::StartServer_Custom_Case()
{
    Server server;
    Validator validator;
    QString address = "127.0.0.1";
    quint64 port64 = 5000;
    if(validator.CheckCustomFields(SERVER, address, port64)){
        quint16 port = quint16(port64);
        server.StartServer(address, port);
        QVERIFY2(server.isListening(), "Server could not start for custom IP address and port");
    }
}

// Purpose: Use the validator to check if the address is valid or not. It should not be.
void Tests::InvalidAddressCase()
{
    // This address is invalid
    QString address = "127.0.0.1.500";
    quint64 port64 = 5000;
    Validator validator;
    QVERIFY2(!validator.IsValidIPAddress(address), "Expected: Invalid IP Address.");
}

// Purpose: Use the validator to check if the port is valid or not. It should not be.
void Tests::InvalidPortCase(){
    // This port is invalid because we are not allowing the use of
    // registered ports that are commonly used by system processes
    quint64 port = 1000;
    Validator validator;
    QVERIFY2(!validator.IsValidPort(port), "Expected: Invalid port number.");
}

// Purpose: Start the server then start the client with a default
// IP address and port to see if the socket is connected.
void Tests::StartClient_Default_Case(){
    // We first need to start the server otherwise the client won't be able to connect.
    Server server;
    server.StartServer(DEFAULT_IP, DEFAULT_PORT);

    // Create the client and start the socket
    Client *client = new Client();
    client->StartSocket(DEFAULT_IP, DEFAULT_PORT);
    QVERIFY2(client->IsSocketConnected(), "Client is not connected.");
}

// Purpose: Start the server then start the client with a custom
// IP address and port to see if the socket is connected.
void Tests::StartClient_Custom_Case(){
    Server server;
    Validator validator;
    QString address = "127.0.0.1";
    quint64 port64 = 5000;
    if(validator.CheckCustomFields(SERVER, address, port64)){
        quint16 port = quint16(port64);
        server.StartServer(address, port);

        Client *client = new Client();
        client->StartSocket(address, port);
        QVERIFY2(client->IsSocketConnected(), "Client is not connected.");
    }
}

// Purpose: Try to start the client with the default IP address and port without having
// had started a server.
void Tests::StartClientWithoutServer_Default_Case(){
    // Create the client and start the socket
    Client *client = new Client();
    client->StartSocket(DEFAULT_IP, DEFAULT_PORT);
    QVERIFY2(!client->IsSocketConnected(), "Client is connected, but should not be.");
}

// Purpose: Try to start the client with the default IP address and port without having
// had started a server.
void Tests::StartClientWithoutServer_Custom_Case(){

    QString address = "127.0.0.1";
    quint16 port = 5000;
    // Create the client and start the socket
    Client *client = new Client();
    client->StartSocket(address, port);
    QVERIFY2(!client->IsSocketConnected(), "Client is connected, but should not be.");
}


// Purpose: Use a xml file that has an invaid format respective to the schema.
// This will throw an error, but will still pass the test.
// Note: It is not necessary to start a server or client, because I am just using the XML
// processor to verify whether or not it is a valid XML or of file type XML.
void Tests::InvalidXMLFormat_Case(){
    // Create file that will be the xml file
    QFile xmlFile;
    QByteArray xmlBytes;

    // Set the file name for the xml file
    xmlFile.setFileName("InvalidFormat.xml");

    // Try to open the xml file
    if(xmlFile.open(QIODevice::ReadOnly | QIODevice::Text)) {

        // Get all the contents of the file and save it into xmlBytes
        xmlBytes = xmlFile.readAll();

        // Close the xml file
        xmlFile.close();

        // Create the xml processor
        XMLProcessor xmlProcessor;
        xmlProcessor.SaveXMLBytes(xmlBytes);

        QVERIFY2(!xmlProcessor.IsValidXML(xmlBytes), "XML file is formatted properly respective to schema. Expected a XML file with an invalid format.");
    }
}

// Purpose: Use a valid xml file against the schema
// Note: It is not necessary to start a server or client, because I am just using the XML
// processor to verify whether or not it is a valid XML or of file type XML.
void Tests::ValidXMLFormat_Case(){
    // Create file that will be the xml file
    QFile xmlFile;
    QByteArray xmlBytes;

    // Set the file name for the xml file
    xmlFile.setFileName("ValidFormat.xml");

    // Try to open the xml file
    if(xmlFile.open(QIODevice::ReadOnly | QIODevice::Text)) {

        // Get all the contents of the file and save it into xmlBytes
        xmlBytes = xmlFile.readAll();

        // Close the xml file
        xmlFile.close();

        // Create the xml processor
        XMLProcessor xmlProcessor;
        xmlProcessor.SaveXMLBytes(xmlBytes);

        QVERIFY2(xmlProcessor.IsValidXML(xmlBytes), "XML file has invalid format respective to schema. Expected a XML file with a valid format.");
    }
}

// Purpose: Send a valid XML file from client to the server.
void Tests::SendXML(){
    // Create file that will be the xml file
    QFile xmlFile;
    QByteArray xmlBytes;

    // Set the file name for the xml file
    xmlFile.setFileName("ValidFormat.xml");

    // Try to open the xml file
    if(xmlFile.open(QIODevice::ReadOnly | QIODevice::Text)) {

        // Get all the contents of the file and save it into xmlBytes
        xmlBytes = xmlFile.readAll();

        // Close the xml file
        xmlFile.close();

        // We first need to start the server otherwise the client won't be able to connect.
        Server server;
        server.StartServer(DEFAULT_IP, DEFAULT_PORT);

        // Create the client and start the socket
        Client *client = new Client();
        client->StartSocket(DEFAULT_IP, DEFAULT_PORT);

        // If we can't write the xml bytes to the client, then throw an error
        QVERIFY2(client->SendXML(xmlBytes), "Could not write xml to socket. Expected: Should have been able to send XML from client to socket");
    }
}

// Purpose: Use a valid XML file against the schema and see if the XML processor can
// retrieve the command. The command should return "Print".
void Tests::ParseKnownCommand(){
    // Create file that will be the xml file
    QFile xmlFile;
    QByteArray xmlBytes;

    // Set the file name for the xml file
    xmlFile.setFileName("KnownCommand.xml");

    // Try to open the xml file
    if(xmlFile.open(QIODevice::ReadOnly | QIODevice::Text)) {

        // Get all the contents of the file and save it into xmlBytes
        xmlBytes = xmlFile.readAll();

        // Close the xml file
        xmlFile.close();

        // Create the xml processor
        XMLProcessor xmlProcessor;
        xmlProcessor.SaveXMLBytes(xmlBytes);

        QCOMPARE(xmlProcessor.GetCommand(), QString("Print"));
    }
}

// Purpose: Use a valid XML file against the schema and see if the XML processor can
// retrieve the command. The command should return "Command is null."
void Tests::ParseUnknownCommand(){
    // Create file that will be the xml file
    QFile xmlFile;
    QByteArray xmlBytes;

    // Set the file name for the xml file
    xmlFile.setFileName("UnknownCommand.xml");

    // Try to open the xml file
    if(xmlFile.open(QIODevice::ReadOnly | QIODevice::Text)) {

        // Get all the contents of the file and save it into xmlBytes
        xmlBytes = xmlFile.readAll();

        // Close the xml file
        xmlFile.close();

        // Create the xml processor
        XMLProcessor xmlProcessor;
        xmlProcessor.SaveXMLBytes(xmlBytes);

        QCOMPARE(xmlProcessor.GetCommand(), QString("Command is null."));
    }
}
QTEST_MAIN(Tests)

#include "tst_tests.moc"
