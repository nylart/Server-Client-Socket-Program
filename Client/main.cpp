#include <QCoreApplication>
#include <QFile>
#include <iostream>
#include <QXmlStreamReader>
#include "global.h"
#include "validator.h"
#include "logoutput.h"
#include "client.h"

void SendXMLData(QString ipAddress, quint16 port, QString fileName){
    LogOutput logger;
    logger.Write("SendXMLData: " + ipAddress + ":" + QString::number(port));
    QFile xmlFile;
    QByteArray xmlBytes;

    // Create a QHostAddress from the default address
    //QHostAddress *ipAddress = new QHostAddress(address);

    xmlFile.setFileName(fileName);

    // Try to open xml file, if it opens successfuly then close and return true
    if(xmlFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        xmlBytes = xmlFile.readAll();
        xmlFile.close();
        logger.Write("SendXMLData -> about to start new client and open socket");
        Client * client = new Client();
        client->OpenSocket(ipAddress, port);

        if(!client->SendXML(xmlBytes)) {
            logger.ThrowError(FailedXML);
        }
    }
    else {
        logger.ThrowError(XMLInvalid);
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Validator validator;
    LogOutput logger;

    QString xmlFileName;
    QFile xmlFile;



    switch(argc){
        case 3:
            // Check if the command line arguments are valid
            if(validator.IsValidArgument(argc, argv)){

                // Convert the passed file name to variable of QString type
                xmlFileName = QString(argv[XML_DEFAULT]);
                if(validator.IsValidXML(xmlFileName)){
                    // Send XML Data to server
                    SendXMLData(DEFAULTIP, DEFAULTPORT, xmlFileName);
                }
                else
                    logger.ThrowError(XMLInvalid);
            }
            else
                // Argument was not default, throw an error.
                logger.ThrowError(Format);
            return 0;
            break;
        case 4:
            // Check if the command line arguments are valid
            if(validator.IsValidArgument(argc, argv)){
                // Convert the passed file name to variable of QString type
                xmlFileName = QString(argv[XML]);

                if(validator.IsValidXML(xmlFileName)){
                    // Get the address and port arguments as variables
                    QString ipAddress = argv[ADDRESS];
                    qint16 port = atoi(argv[PORT]);

                    // Send XML Data to server
                    SendXMLData(ipAddress, port, xmlFileName);
                }
                else
                    logger.ThrowError(XMLInvalid);
            }
            else
                // Argument was not default, throw an error.
                logger.ThrowError(Format);
            return 0;
            break;
        default:
            // Not the right number of command line arguments.
            logger.ThrowError(Format);
            return 0;
            break;

    }

    return a.exec();
}
