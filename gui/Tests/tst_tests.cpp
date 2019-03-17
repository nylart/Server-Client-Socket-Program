#include <QtTest>
#include <QTest>
#include <QCoreApplication>
#include "server.h"
#include "global.h"
#include "client.h"
#include "validator.h"

// add necessary includes here

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
    void InvalidAddressCase();
    void InvalidPortCase();
    void InvalidXMLCase();
    void WriteXMLtoClient();

private:

};

Tests::Tests()
{
}

Tests::~Tests()
{

}

void Tests::StartServer_Default_Case()
{
    Server server;
    server.StartServer(DEFAULT_IP, DEFAULT_PORT);
    QVERIFY2(server.isListening(), "Server could not start for default IP address and port");
}

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

void Tests::InvalidAddressCase()
{
    // This address is invalid
    QString address = "127.0.0.1.500";
    quint64 port64 = 5000;
    Validator validator;
    QVERIFY2(!validator.IsValidIPAddress(address), "Expected: Invalid IP Address.");
}

void Tests::InvalidPortCase(){
    // This port is invalid because we are not allowing the use of
    // registered ports that are commonly used by system processes
    quint64 port = 1000;
    Validator validator;
    QVERIFY2(!validator.IsValidPort(port), "Expected: Invalid port number.");
}

void Tests::StartClient_Default_Case(){
    // Create the client and start the socket
    Client *client = new Client();
    client->StartSocket(DEFAULT_IP, DEFAULT_PORT);
    QVERIFY2(client->IsSocketConnected(), "Client is not connected.");
}

void Tests::StartClient_Custom_Case(){

}


void Tests::InvalidXMLCase(){

}

void Tests::WriteXMLtoClient(){

}

QTEST_MAIN(Tests)

#include "tst_tests.moc"
