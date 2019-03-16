Konami Socket Programming Project - Tralyn Le

## Purpose
    The purpose of this project is to utilize server and client communication by sending XML data
    via sockets. 

## How to Run
1. Deploy the server
    a) Open a new terminal
    b) Navigate to the directory Server/build-Server-Release
       Note: You may need to run make in this directory in order to execute the Server.
    c) In the terminal, write either:   
        - ./Server default
        OR
        - ./Server <IPADDRESS> <PORT>
          ex) ./Server 127.0.0.1 5000
       Note: Writing any non-expected arguments will throw an error.
    d) The server should now be deployed and listening 

2. Deploy the Client
    a) Open a new terminal
    b) Navigate to the directory Client/build-Client-Release
       Note: You may need to run make in this directory in order to execut the Client.
    c) In the terminal, write either:   
        - ./Server default <XMLFILE>
          ex) ./Server default xmlSample_Print.xml
        OR
        - ./Server <IPADDRESS> <PORT> <XMLFILE>
          ex) ./Server 127.0.0.1 5000 xmlSample_Print.xml
       Note: Writing any non-expected arguments will throw an error.
    d) The client should now be deployed and send the XML data to the server.


## Server-side Design
    The Server Directory:
    - Server
        - global.h
        - logoutput.h
        - logoutput.cpp
        - main.cpp
        - receiver.cpp
        - receiver.h
        - server.cpp
        - server.h
        - validator.cpp
        - validator.h
        - xmlprocessor.cpp
        - xmlprocessor.h
        - xmlSchema.xsd
    
    The server-side maintains and utilizes the main program (main.cpp) and five objects (LogOutput, Receiver, Server, Validator, and XMLProcessor). The main program will check the command line arguments to verify that the arguments are formatted as expected, then will use the validator to determine if the IP Address and Port are valid. If those conditions are met, it will start the Server. 

    The Server will attempt to connect to the passed IP Address and port. If it succeeds, then it will listen for any incoming connection from the client-side via the Receiver. 

    The Receiver will connect to the socket from the client-side. When there is new data available for the receiver, it will read the data then start a thread to utilize the XMLProcessor. With each new thread, a new XMLProcessor object is instantiated. Due to this nature, I did not use mutexes because the same data / critical section is not accessed by multiple threads. 

    The XMLProcessor will receive the XML data from the Receiver, then validate whether or not it is a valid XML file. If it is, then it will retrieve the "commands" from the XML. The XMLProcessor checks the XML against an XML schema I created using xmlgrid.net. I explain the reason why I decided to verify the data against the schema in the XMLProcessor.cpp file. Once it hwas finished retrieving the commands, it emits a signal back to the Receiver to let the receiver know that it is finished.

    The Receiver has now received the parsed commands from the XMLProcessor. It will create an OutputXML.xml file that will contain the response expected from the project description. It will also output the XML Response data to the terminal. 

    Note: LogOutput is used for writing to the console and throwing errors. Since the errors can be thrown in multiple places, I wanted to create an object that would allow me to only have to edit error messages in one place. Most files utilize the global.h header file which contains constant variables for the project. 

## Client Design
    The Client Directory:
    - Client
        - global.h
        - logoutput.h
        - logoutput.cpp
        - main.cpp
        - client.cpp
        - client.h
        - validator.cpp
        - validator.h
        - xmlSample_Print.xml
        - xmlSample_Unknown.xml

    The client-side maintains and utilizes the main program (main.cpp) and three objects (LogOutput, Client, and Validator). The main program will check the command line arguments to verify that the arguments are formatted as expected, then will use the validator to determine if the IP Address and Port are valid. Next, it will open the XML file and get all the contents of the XML file, then start the Client at the given IP Address and Port with the contents of the file.
    
    The Client will connect to the socket that the server should also be running on. If there is no open connection to the socket, it will throw an error. Thus, the server must be running beforehand. If the socket is open and connected, the client will send the data over to the server. The client's job is now done and will disconnect when the terminal is closed.

    The server will be responsible for handling that data, verifying if it is a valid XML and has expected formatting, then output the data to the server-side monitor.

    Note: LogOutput is used for writing to the console and throwing errors. The errors on client-side differ slightly from the errors on server-side. Since the errors can be thrown in multiple places, I wanted to create an object that would allow me to only have to edit error messages in one place. Most files utilize the global.h header file which contains constant variables for the project. 


## Thoughts, Approaches, and Future Implementation

    - Design approaches
    I considered utilizing an event system that was more specifically geared towards Publisher and Subscriber rather than Server and Client, however the project description said Server and Client so I went with that. 

    - Multithreading & Mutexes
    Since the Receiver on server-side maintains a Threadpool which in turn maintains the threads, it is possible to send multiple messages from the client side to the server. I did not utilize mutexes since the threads are never executing the same object instance's critical section.

    - Unit Testing
    I attempted to write unit tests to run tests against the client and server files to make sure they were behaving as expected, however I ran out of time and deleted them since they were not fully functional. I will continue to work on the unit testing even after the project deadline, because it's something that I wanted to do. 

    - GUI
    I didn't make this project a GUI because I wanted to focus on getting the underlying project working properly and if I had more time then I would work on the GUI. Again, I will continue working on this past the deadline to see it through.
