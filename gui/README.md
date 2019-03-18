Konami Socket Programming Project GUI - Tralyn Le

## Purpose
    The purpose of this project is to utilize server and client communication by sending XML data
    via sockets. 


## How to Run the GUI

Note: I'm assuming you're in the "gui" folder already.

1. Run the Program
    a) Open a new terminal
    b) Navigate to the directory: build-SocketProgram-Desktop-Release
       Note: You may need to run make in this directory in order to execute the program.
    c) To start the program, type the following in the terminal: 
            ./SocketProgram
    d) The GUI program should now be showing and should be in the "Server" tab.

2. Start the Server
    a) If you want to start the server with the default IP address and port, then make sure the radio button has "Default" checked, then press "Start Server". 
    b) If you want to start the server with a custom IP address and port, then click the "Custom" radio button then type the desired IP address and port in the fields. Then press "Start Server".

3. Start the Client
    a) If the server is already running, click the "Client" tab.
    b) If you want to start the client with the default IP address and port, then make sure the radio button has "Default" checked. 
    c) If you want to start the client with a custom IP address and port, then click the "Custom" radio button then type the desired IP address and port in the fields.
    d) Click the "Browse XML" button to select a XML file.
    e) Press "Start Client".

Note: You can click back and forth between the Server and Client tabs to see the output.


## How to Run the Unit Tests

Note: I'm assuming you're in the "gui" folder already.

    1. Open the terminal.
    2. Navigate to the directory: build-Tests-Desktop-Release
       Note: You may need to run make in this directory in order to execute the program.
    3. Type the following into the terminal:
        ./Tests


## What's the Difference?

    I already submitted a base version of this socket program last Friday, however I didn't get the chance to really do all that I wanted to do for this program. So here are a few things that make this version different from the previous submission.

        - GUI Program
            - I created a GUI program that will make it easier to run both the client and server as well as viewing output between both.

        - Unit Testing
            - The unit testing is a standalone project that utilizes the source files in "SocketProgram" but does not utilize the GUI. I wanted to make sure I created a unit test that would make checking for errors easier, but also just because it is good practice to do so.

        - Got rid of LogOutput
            - Since I am no longer writing out to the console and instead am displaying messages to the GUI, I use signals and slots to emit messages to the GUI when they need to be displayed. Part of why I wanted to get rid of LogOutput is because to make this work I would have to make LogOutput a singleton, which is just not ideal. 

        - Got rid of Error Types (& LogOutput.ThrowError())
            - I made global constant variables for my errors so that I could access them easier and only have to edit them if need be in one place.


## Source Files 
    SocketProgram/
        - global.h
        - main.cpp
        - receiver.cpp
        - receiver.h
        - server.cpp
        - server.h
        - validator.cpp
        - validator.h
        - xmlprocessor.cpp
        - xmlprocessor.h
        - client.cpp
        - client.h
    Tests/
        - tst_tests.cpp

## Additional Files

    - xmlSample_Print.xml
    - xmlSample_Unknown.xml
    - xmlSchema.xsd


## Server-side Design

    The server-side maintains and utilizes four objects (Receiver, Server, Validator, and XMLProcessor). When the user runs the GUI program and starts the server, they will need to choose between using the default IP address and port or entering a custom IP address and port. The program will use the validator to determine if the user-given IP address and port are valid. If those conditions are met, it will start the Server. 

    The Server will attempt to connect to the passed IP Address and port. If it succeeds, then it will listen for any incoming connection from the client-side via the Receiver. 

    The Receiver will connect to the socket from the client-side. When there is new data available for the receiver, it will read the data then start a thread to utilize the XMLProcessor. With each new thread, a new XMLProcessor object is instantiated. Due to this nature, I did not use mutexes because the same data / critical section is not accessed by multiple threads. 

    The XMLProcessor will receive the XML data from the Receiver, then validate whether or not it is a valid XML file. If it is, then it will retrieve the "command" from the XML. The XMLProcessor checks the XML against an XML schema I created using xmlgrid.net. I explain the reason why I decided to verify the data against the schema in the XMLProcessor.cpp file. Once it has finished retrieving the commands, it emits a signal back to the Receiver to let the receiver know that it is finished.

    The Receiver has now received the parsed commands from the XMLProcessor. It will create an OutputXML.xml file that will contain the response expected from the project description. It will also output the XML Response data to the GUI. 


## Client Design

    The client-side maintains and utilizes two objects, the Client and Validator. When the user runs the GUI program and starts the server, they will need to choose between using the default IP address and port or entering a custom IP address and port. The program will use the validator to determine if the user-given IP address and port are valid. The user must also select an XML file to send from the client to the server. Once the user has pressed "Start Client", the program will open the XML file and get all the contents of the XML file, then try to start the Client at the given IP Address and Port with the contents of the file.
    
    The Client will connect to the socket that the server should also be running on. If there is no open connection to the socket, it will throw an error. Thus, the server must be running beforehand. If the socket is open and connected, the client will send the data over to the server. The client's job is now done and will disconnect when the program is closed.

    The server will be responsible for handling that data, verifying if it is a valid XML and has expected formatting, then output the data to the server-side monitor.

## Unit Tests
    I wrote these test cases to easily check for errors and make sure my code is functioning as expected. Due to the nature of this unit test project not being run on target with the GUI, I made the unit test project use the source and header files from the SocketProgram. The aim is to check that each of my classes (Server, Client, Receiver, XMLProcessor, and Validator) are functioning appropriately. 

    Test Cases:
        - StartServer_Default_Case()
            - Start the server with the default IP address and default port (defined in global.h). If the server started and is listening, then the test is successful.

        - StartServer_Custom_Case()
            - Start the server with a custom IP address and custom port. If the server started and is listening, then the test is successful.

        - StartClient_Default_Case()
            - Starts the server and client with the default IP address and default port. If the socket is connected, then the test is successful.

        - StartClient_Custom_Case()
            - Starts the server and client with a custom IP address and custom port. If the socket is connected, then the test is successful.

        - StartClientWithoutServer_Default_Case()
            - Starts the client with the default IP address and default port, however there is no server running. If the socket is NOT connected, then the test is successful.

        - StartClientWithoutServer_Custom_Case()
            - Starts the client with a custom IP address and custom port, however there is no server running. If the socket is NOT connected, then the test is successful.

        - InvalidAddressCase()
            - Check an invalid address string with the Validator's IsValidIPAddress() function. If this function returns false, then the test is successful.

        - InvalidPortCase()
            - Check an invalid port with the Validator's IsValidPort() function. If this function returns false, then the test is successful.

        - InvalidXMLFormat_Case()
            - Uses the XML Processor to check whether or not the XML file "InvalidFormat.xml" has a valid format respective to the schema. If the function returns false, then the test is successful. 

        - ValidXMLFormat_Case()
            - Uses the XML Processor to check whether or not the XML file "ValidFormat.xml" has a valid format respective to the schema. If the function returns true, then the test is successful. 

        - SendXML()
            - Start a server and client then try to send the XML data from the client. If it sends successfully, then the test is successful.

        - ParseKnownCommand()
            - Use the XML Processor to try to parse a valid XML file (respective to the schema). The schema is expecting a "Command" tag. If the XML Processor returns the command "Print", then the test is successful.

        - ParseUnknownCommand()
            - Use the XML Processor to try to parse a valid XML file (respective to the schema). The schema is expecting a "Command" tag. If the XML Processor returns the command "Command is null.", then the test is successful.


    Note: At first I thought to create a test case that would check if a file type for the XML is of valid XML file type, however the way I designed it with the GUI only allows for the user to select a file that is of XML file type. However, it is possible to check for formatting errors with the XMLs.


## Thoughts, Approaches, and Future Implementation

    - Design approaches

    Ref 1: http://www.ni.com/tutorial/53679/en/
    Ref 2: https://vichargrave.github.io/tcp-ip-network-programming-design-patterns-in-cpp/

    I considered utilizing an event system that was more specifically geared towards Publisher and Subscriber rather than Server and Client, however the project description said Server and Client so I went with that. I looked into best practice design patterns for server and client applications and more specifically server and client applications that send and receive data over sockets.

    I could have made the server a singleton, however I decided to design it as a connection manager instead (shown in Ref 1). The program provides a mechanism to store and retrieve the connection information the server should run on, as well as the client connection information. The server listen (via the connection) for any new information from the clients.

    The actual functionality of how the server and client interact is modeled after Ref 2's "Socket Workflow" diagram.


    - Multithreading & Mutexes

    Since the Receiver on server-side maintains a Threadpool which in turn maintains the threads, it is possible to send multiple messages from the client side to the server. However, I did not utilize mutexes since the threads used for the XMLProcessor are never executing the same object instance's critical section.

    - Thoughts & Takeaways

    I've never used Qt before so I watched quite a few Youtube tutorials to see how things were done. I researched for quite a bit how to structure the Qt project files and I'm still not sure if I structured it in a typical/efficient way. Please let me know what would have been better. The reason I ask this is because I initially wanted to add another tab to the GUI for unit testing. I planned to let the user start the unit tests and see the output inside the program, with a nice functional progress bar for decorum. However, because of how Qt runs unit test projects I was unable to make it work inside of the GUI. This had to do with multiple main() functions because of the QTEST_MAIN(Tests) and the main.cpp. I could have just made a "Tests" class inside the normal SocketProgram project that the MainWindow class would have access to. However I wanted to make use of the automated functionality the Qt libraries provided. 

    I originally submitted the "console" version of this project that runs everything explicitly through the terminal. The underlying architecture for it was okay for the purpose of making it work, however I didn't want to just stop working on this project just because I submit it already. So I created the GUI version and created unit tests for this version of the project. 

    Thanks for this assignment! I had a lot of fun working on this project. It was different from what I'm accustomed to doing. 

