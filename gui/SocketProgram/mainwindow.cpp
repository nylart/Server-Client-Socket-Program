#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Initial Setup
    HideCustomBoxes();

    // Listen for when these buttons are clicked
    connect(ui->DefaultRadioButton_Client, SIGNAL(clicked()), this, SLOT(on_DefaultRadioButton_Client_clicked()));
    connect(ui->DefaultRadioButton_Server, SIGNAL(clicked()), this, SLOT(on_DefaultRadioButton_Server_clicked()));
    connect(ui->CustomRadioButton_Client, SIGNAL(clicked()), this, SLOT(on_CustomRadioButton_Client_clicked()));
    connect(ui->CustomRadioButton_Server, SIGNAL(clicked()), this, SLOT(on_CustomRadioButton_Server_clicked()));
    connect(ui->BrowseXMLButton, SIGNAL(pressed()), this, SLOT(on_BrowseXMLButton_clicked()));

    // Listen for when the server emits messages to write to the server text area
    connect(&server, SIGNAL(updateServerText(QString)), this, SLOT(do_UpdateServerText(QString)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

// ================================================================================ Update Text Area Related Signals

// Callback: The client has emitted a message and this function is the slot.
// Purpose: Write out to the text area in the client tab the passed message.
void MainWindow::do_UpdateClientText(QString message){
    ui->TextArea_Client->append(message + "\n");
}

// Callback: The server has emitted a message and this function is the slot.
// Purpose: Write out to the text area in the server tab the passed message.
void MainWindow::do_UpdateServerText(QString message){
    ui->TextArea_Server->append(message + "\n");
}

// ================================================================================ Client Related Signals

// Callback: Default radio button in client tab has been clicked.
// Purpose: Hide the IP address and port boxes, since they're only used for custom
void MainWindow::on_DefaultRadioButton_Client_clicked(){
    ui->CustomRadioButton_Client->setChecked(false);
    HideCustomBoxes();
}

// Callback: Custom radio button in client tab has been clicked.
// Purpose: Show the IP address and port boxes, since they're used for custom
void MainWindow::on_CustomRadioButton_Client_clicked(){
    ui->DefaultRadioButton_Client->setChecked(false);
    ui->IPAddressBox_Client->show();
    ui->PortBox_Client->show();
}

// Callback: Browse XML Button has been clicked.
// Purpose: Allow user to choose which XML file they will send.
void MainWindow::on_BrowseXMLButton_clicked(){
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open XML File"),"C://","XML Files (*.xml)");
    //QMessageBox::information(this, tr("File Name"), fileName);
    ui->xmlFileNameBox->setText(fileName);
    ui->xmlFileNameBox->setReadOnly(true);
}

// Callback: Start Client Button has been clicked.
// Purpose: Check if the user has selected default or custom, then try to start the client.
void MainWindow::on_StartClientButton_clicked(){
    // XML File related variables
    QByteArray xmlBytes;
    QFile xmlFile;

    // QString that will store user given IP address
    QString ipAddress;
    quint16 port;

    // If the custom radio button is checked,
    if(ui->CustomRadioButton_Client->isChecked()){
        // Check the IP address, port, and xml file fields to make sure they're not empty.
        if(CheckCustomFields(CLIENT)){
            ipAddress = ui->IPAddressBox_Client->text();
            port = ui->PortBox_Client->text().toUShort();
        }
    }
    else if(ui->DefaultRadioButton_Client->isChecked()){
        ipAddress = DEFAULT_IP;
        port = DEFAULT_PORT;
    }

    if(!ui->xmlFileNameBox->text().isEmpty()){
        xmlFile.setFileName(ui->xmlFileNameBox->text());
        // Try to open the xml file
        if(xmlFile.open(QIODevice::ReadOnly | QIODevice::Text)) {

            // Get all the contents of the file and save it into xmlBytes
            xmlBytes = xmlFile.readAll();

            // Close the xml file
            xmlFile.close();

            // Create the client and start the socket
            Client *client = new Client();
            client->StartSocket(ipAddress, port);

            // Listen to the client to transmit any incoming messages
            connect(client, SIGNAL(updateClientText(QString)), this, SLOT(do_UpdateClientText(QString)));

            // If we can't write the xml bytes to the client, then throw an error
            if(!client->SendXML(xmlBytes)) {
                do_UpdateClientText(SOCKET_WRITE_ERROR);
                return;
            }
        }
        else{
            // The file could not open, so throw an error
            do_UpdateClientText(INVALID_XML_ERROR);
            return;
        }
    }
    else {
        // The file is empty, so throw an error
        do_UpdateClientText(INVALID_XML_ERROR);
        return;
    }
}

// ================================================================================ Server Related Signals

// Callback: Default radio button in server tab has been clicked.
// Purpose: Hide the IP address and port boxes, since they're only used for custom
void MainWindow::on_DefaultRadioButton_Server_clicked(){
    ui->CustomRadioButton_Server->setChecked(false);
    HideCustomBoxes();
}


// Callback: Custom radio button in serber tab has been clicked.
// Purpose: Show the IP address and port boxes, since they're used for custom
void MainWindow::on_CustomRadioButton_Server_clicked(){
    ui->DefaultRadioButton_Server->setChecked(false);
    ui->IPAddressBox_Server->show();
    ui->PortBox_Server->show();
}

// Callback: Start Server Button has been clicked.
// Purpose: Check if the user has selected default or custom, then try to start the server.
void MainWindow::on_StartServerButton_clicked(){
    // If the custom radio button is checked,
    if(ui->CustomRadioButton_Server->isChecked()){
        // Check the IP address and port fields to make sure they're not empty.
        if(CheckCustomFields(SERVER)){
            QString ipAddress = ui->IPAddressBox_Server->text();
            quint64 port64 = ui->PortBox_Server->text().toLongLong();
            quint16 port = ui->PortBox_Server->text().toUShort();

            // Try to start a server with passed ip address and port
            server.StartServer(ipAddress, port);
        }
    }
    // Check if the default radio button is checked
    else if(ui->DefaultRadioButton_Server->isChecked()){
        // Try to start a server with default ip address and port
        server.StartServer(DEFAULT_IP, DEFAULT_PORT);
    }
}


// ================================================================================ Custom Fields Related

// Purpose: Hides the custom field boxes such as IP Address
// and Port in both client and server tabs
void MainWindow::HideCustomBoxes(){
    ui->IPAddressBox_Client->hide();
    ui->PortBox_Client->hide();
    ui->IPAddressBox_Server->hide();
    ui->PortBox_Server->hide();
}


// Purpose: Check for errors (such as if the fields are empty) where we will not be able to
// proceed with trying to start the server.
bool MainWindow::CheckCustomFields(QString type){

    QString address;
    quint64 port64;

    // Set the correct values from the correct fields
    if(type == SERVER){
        address = ui->IPAddressBox_Server->text();
        port64 = ui->PortBox_Server->text().toLongLong();
    }
    else if (type == CLIENT){
        address = ui->IPAddressBox_Client->text();
        port64 = ui->PortBox_Client->text().toLongLong();
    }

    // If the text is empty or not valid, throw error
    if(address.isEmpty() || !validator.IsValidIPAddress(address)){
        if(type == SERVER)
            do_UpdateServerText(INVALID_ADDRESS_ERROR);
        else if (type == CLIENT)
            do_UpdateClientText(INVALID_ADDRESS_ERROR);

        return false;
    }

    // If the port is invalid, throw an error.
    if(!validator.IsValidPort(port64)){
        if(type == SERVER)
            do_UpdateServerText(INVALID_PORT_ERROR);
        else if (type == CLIENT)
            do_UpdateClientText(INVALID_PORT_ERROR);

        return false;
    }

    // If we made it this far, then allow the program to try to start the server next
    return true;
}
