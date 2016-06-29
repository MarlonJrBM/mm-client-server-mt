#include "TCPMTServer.h"

#include <iostream>

#include "ServerApplication.h"
#include "TP3_constants.h"

using namespace std;
using namespace TP3;


void TCPMTServer::setUp(const string& port) {

    //helper variable to check for errors
    int returnCode = -1; 
    if (LOGGING) {
        cout << "Binding server..." << endl;
    }
    
    _serverSocketId = socket(AF_INET6, SOCK_STREAM, 0);
    
    if (_serverSocketId < 0) {
        cout << "ERROR setting up socket" << endl;
        exit(1);
    }
    
    //Initializing socket structure
    //in6addr_any allows connection from both ipv6 and ipv4
    bzero(&_serverSocket, sizeof(_serverSocket));
    _serverSocket.sin6_family = AF_INET6;
    _serverSocket.sin6_port = htons(stoi(port));
    _serverSocket.sin6_addr = in6addr_any;

    returnCode = bind(_serverSocketId, (sockaddr*) &_serverSocket, sizeof(_serverSocket));
    if (returnCode < 0 ) {
        cout << "ERROR binding server socket." << endl;
        cout << "Maybe try a different port?" << endl;
        exit(1);
    }

    listen(_serverSocketId, MAX_NUM_CONNECTIONS );
}

void TCPMTServer::closeConnection(int clientId) {
    if (LOGGING) {
        cout << "Closing connection to client..." << endl;
    }

    //TODO - remove client from _clientList (in the future)
    
    sendMessageToClient(clientId,"-1");

    if (LOGGING) {
        cout << "Client is out" << endl;
    }
}


string TCPMTServer::getMessageFromClient(int clientId) {
    if (LOGGING) {
        cout << "Waiting for client message" << endl;
    }

    char msg[MAX_BUF];

    recv(clientId,msg,MAX_BUF, 0);

    if (LOGGING) {
        cout << "Got client message: " << msg << endl;
    }
   
    return string(msg);

}


void TCPMTServer::sendMessageToClient(int clientId, const string& message) {
    if (LOGGING) {
        cout << "Sending message to client: " << message << "." << endl;
    }

   if (send(clientId, message.c_str(), message.size()+1, 0) < 0) {
        cout << "I can't send message back to client. I give up!" << endl;
        exit(1);
   } 
}

int TCPMTServer::acceptClient() {
    if (LOGGING) {
        cout << "Waiting for client" << endl;
    }
    
    int clientSocketId = -1;

    clientSocketId = accept(_serverSocketId, NULL, 0);

    if (clientSocketId < 0) {
        cout << "ERROR when accepting new client!" << endl;
        exit(1);
    }
    
    if (LOGGING) {
        cout << "Client accepted..." << endl;
    }

    return clientSocketId;
}