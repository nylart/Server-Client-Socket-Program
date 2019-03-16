#include "xmlprocessor.h"
#include "validator.h"
#include "global.h"

XMLProcessor::XMLProcessor()
{
}

// Purpose: Process the XML and retrieve the commands from it
void XMLProcessor::run() {
    Validator validator;
    QByteArray commands;

    // if the xmlByteArray has data in it
    if(!xmlByteArray.isNull()) {

        // check that the data is valid xml format
        if(IsValidXML()) {

            // If it is XML, pass to a work queue that “processes” the command
            commands.append(GetCommand());
        }
        else
            //Invalid XML should result in a display of “Unknown Command”
            commands.append("Unknown Command");
    }
    else {
        // The xmlByteArray does not have data
        logger.ThrowError(InvalidXML);
    }

    // Manually emit a signal with the commands
    emit Result(commands);
}

// Purpose: Save the xml byte array to this class
//
// Thought: This is a safer approach to store the xml bytes to the object. We
// don't have to worry about the threads accessing this specific xml bytes array
// because the XMLProcessor is being instantiated in each thread, so they are
// not accessing the same XMLProcessor anyways.
void XMLProcessor::SaveXMLBytes(QByteArray xmlBytes){
    xmlByteArray = xmlBytes;
}

// Purpose: Check the xml against the xml schema to return whether or not it is a valid xml.
//
// Thought: I considered several different approaches for this. I thought about using external
// third party XML parser libraries (https://stackoverflow.com/questions/9387610/what-xml-parser-should-i-use-in-c)
// but for this project I thought it would overcomplicate the task. So then I thought about using either
// <!DOCTYPE ...> or using an XML Schema. Although the <!DOCTYPE ...> method would be easier and wouldn't rely on
// a specific formatting (from the schema), I think it's best to use the schema to ensure the XML data we are receiving
// is structured in a way that we expect it.
bool XMLProcessor::IsValidXML() {
    QUrl schemaFile("file:xmlSchema.xsd");
    QBuffer buffer(&xmlByteArray);
    buffer.open(QIODevice::ReadOnly);

    QXmlSchema schema;
    schema.load(schemaFile);

    if(schema.isValid()) {
        QXmlSchemaValidator validator(schema);
        return validator.validate(&buffer);
    }
    else {
        logger.ThrowError(Schema);
    }

    return false;
}

// Purpose: Parse through the xmlBytes and return the command from the xml.
//
// Thought: Decided to use the QXmlStreamReader because the code itself drives
// the loop and pulls tokens from the reader, one after another, as it needs them.
QString XMLProcessor::GetCommand() {
    QXmlStreamReader reader(xmlByteArray);
    QString command = "Command is null.";

    // Have XML Stream reader parse through the xml to find the command
    while(!reader.atEnd()) {
        if(reader.isStartElement()) {
            if(reader.name() == COMMAND) {
                reader.readNext();
                if(reader.atEnd())
                    break;

                if(reader.isCharacters()) {
                    command = reader.text().toString();
                    break;
                }
            }
        }
        reader.readNext();
    }
    return command;
}

