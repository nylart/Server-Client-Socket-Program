#include <QCoreApplication>
#include <QDebug>
#include <QHostAddress>
#include <QFile>
#include <QXmlStreamReader>
#include "validator.h"
#include "logoutput.h"
#include "client.h"
#include "global.h"



// Thought: In practice, I generally really dislike having functions that do too many different things or are too long.
// I tried creating new functions to check the arguments with greater ease via the Validator, but then the code in main()
// wasn't as clear and straightforward.
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    // Logger will be used to write output or throw errors
    LogOutput logger;

    // Validator that is used to check arguments passed
    Validator validator;

    // QString that will store user given IP address
    QString ipAddress;

    // Ports of 64-bit and 16-bit
    quint64 port64;
    quint16 port16;

    // Variables necessary for the xml file
    QString xmlFileName;
    QByteArray xmlBytes;
    QFile xmlFile;

    // Holds whether or not we will check the XML file
    bool proceedXMLCheck = false;


    // Check the passed arguments from the command line
    switch(argc){
        case 3:
        // Check if the command line arguments passed "default"
        if(QString(argv[ADDRESS]) == DEFAULT){
            // Convert the passed file name to variable of QString type
            xmlFileName = QString(argv[XML_DEFAULT]);

            // Set the IP Address and port to be of default, so that it's easier to start the client later.
            // Thought: I could have just used DEFAULT_IP and DEFAULT_PORT later on in my proceedXMLCheck condition,
            // however then I would have to check again if the argument passed was "default". Since I already am checking it here,
            // this was just more efficient.
            ipAddress = DEFAULT_IP;
            port16 = DEFAULT_PORT;

            // Set this to true so we can know to check the xml file and potentially start the client
            proceedXMLCheck = true;
        }
        else {
            // Argument was not default but had 2 arguments, throw an error.
            logger.ThrowError(Format);
            return 0;
        }
        break;

        case 4:
            // Store passed arguments for ease of use
            ipAddress = QString(argv[ADDRESS]);
            port64 = QString(argv[PORT]).toLongLong();

            // Check if the IP Address passed is valid
            if(validator.IsValidIPAddress(ipAddress)){

                // Check if the port passed is valid
                if(validator.IsValidPort(port64)){

                    // Cast port16 to be a 16-bit uint
                    port16 = quint16(port64);

                    // Convert the passed file name to variable of QString type
                    xmlFileName = QString(argv[XML]);

                    // Set this to true so we can know to check the xml file and potentially start the client
                    proceedXMLCheck = true;
                }
                else{
                    // Port was invalid, throw an error
                    logger.ThrowError(Port);
                    return 0;
                }
            }
            break;
        default:
            logger.ThrowError(Format);
            return 0;
    }

    // Purpose: If true, check the XML file passed and if we can open it, start the client
    // Thought: I originally wanted to create a new function to handle the checking of the XML file
    // and starting of the client, however when I did I would get finicky behavior from passing the
    // QFile. So in order to get this working for the project I did it inside here where I knew my variables
    // were still easily accessible.
    if(proceedXMLCheck){

        // Set the file name for the xml file
        xmlFile.setFileName(xmlFileName);

        // Try to open the xml file
        if(xmlFile.open(QIODevice::ReadOnly | QIODevice::Text)) {

            // Get all the contents of the file and save it into xmlBytes
            xmlBytes = xmlFile.readAll();

            // Close the xml file
            xmlFile.close();

            // Create the client and start the socket
            Client *client = new Client();
            client->StartSocket(ipAddress, port16);

            // If we can't write the xml bytes to the client, then throw an error
            if(!client->SendXML(xmlBytes)) {
                logger.ThrowError(SocketWrite);
                return 0;
            }
        }
        else {
            // The file could not open, so throw an error
            logger.ThrowError(InvalidXML);
            return 0;
        }
    }

    return a.exec();
}
