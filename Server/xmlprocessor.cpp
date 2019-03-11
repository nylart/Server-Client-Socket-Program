#include <QRunnable>
#include "xmlprocessor.h"
#include "validator.h"
#include "logoutput.h"

XMLProcessor::XMLProcessor()
{

}

// Save the xml byte array to this class
void XMLProcessor::SaveXMLBytes(QByteArray xmlBytes){
    xmlByteArray = xmlBytes;
}

QString XMLProcessor::GetCommand(){
    QXmlStreamReader reader(xmlByteArray);
    QString commandText = "Item not found";

    while(!reader.atEnd()) {
        if(reader.isStartElement()) {
            if(reader.name() == "Command") {
                reader.readNext();
                if(reader.atEnd())
                    break;

                if(reader.isCharacters()) {
                    commandText = reader.text().toString();
                    break;
                }
            }
        }
        reader.readNext();
    }
    return commandText;
}

void XMLProcessor::Run() {
    Validator validator;
    QByteArray buffer;

    // if the xmlByteArray has data in it
    if(!xmlByteArray.isNull()) {
        // check that the data is valid xml format
        if(validator.IsValidXML(xmlByteArray)) {
            // If it is XML, pass to a work queue that “processes” the command
            buffer.append(GetCommand());
        }
        else {
            //Invalid XML should result in a display of “Unknown Command”
            buffer.append("Unknown Command");
        }
    }
    else {
        // The xmlByteArray does not have data
        logger.ThrowError(InvalidXML);
    }

    //Finally send a signal to the server, that says "HERES YOUR RESULT"
    emit Result(buffer);
}
