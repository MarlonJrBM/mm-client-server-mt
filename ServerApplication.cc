#include "ServerApplication.h"

#include <iostream>

#include "TCPMTServer.h"
#include "Ranking.h"
#include "TP3_constants.h"

using namespace std;
using namespace TP3;


TCPMTServer* TCPMTServer::_serverInstance = NULL;
Ranking* ServerApplication::_timeRanking = NULL;
pthread_mutex_t ServerApplication::_lock;

int ServerApplication::runApplication(int argc, char** argv) {

    //Local and helper variables
    int curClient = -1;
    string port = argv[1];
    pthread_t tid;
    _numClients = 0;

    //pthread-related stuff initialization
    if (pthread_mutex_init(&_lock, NULL) != 0) {
        printf("\n mutex init failed\n");
        return 1;
    }


    
    if (LOGGING) {
        cout << "Starting server!" << endl;
        cout << "Number of arguments: " << argc << endl;
        cout << "Press ctrl + c at anytime to exit" << endl;
    }

    TCPMTServer* server = TCPMTServer::getInstance();

    //Sets up server configuration and structures
    server->setUp(port);

    //initializes structure to handle race times
    _timeRanking = new Ranking();

    //Server's main loop
    while (true) {
        //Below calls are blocking, will wait until
        //Client connects and opens new thread
        curClient = server->acceptClient();
        _numClients++;
        _clientList.push_back(curClient); 
        _tidList.push_back(tid);

        //creating new thread
        if (pthread_create(&(_tidList[_numClients - 1]), NULL, processClient, (void*)&_clientList[_numClients-1]) != 0) {
            cout << "Error when accepting client with id " << curClient << endl;
            exit(1);
        }
    }

    //Will never reach below lines in single-threaded version
    server->stop();

    return 0;

}

bool ServerApplication::isClosingSignal(const string& message) {
    int signal = stoi(message);

    if (signal < 0) 
        return true;
    else
        return false;
}

bool ServerApplication::isValidMessage(const string& message) {
    return strtoll(message.c_str(), NULL, 10);
}


ServerApplication::~ServerApplication() {
    TCPMTServer::deleteInstance();
    if (!_timeRanking) delete(_timeRanking);
    pthread_mutex_destroy(&_lock);
}

void* ServerApplication::processClient(void* clientData) {

    bool isClosingMessage = false;
    TCPMTServer* server = TCPMTServer::getInstance();
    unsigned curClient = *((unsigned*) clientData);
    string clientMessage = "";
    string position = "";

    if (LOGGING) {
        cout << "Opening new connection to client " << curClient << endl;
    }

    do {
        clientMessage = server->getMessageFromClient(curClient);
        isClosingMessage = isClosingSignal(clientMessage);

        if (isClosingMessage) {
            server->closeConnection(curClient);
            continue;
        }

        //First, we'll check if client sends a valid message
        //This is just a basic server-side input validation
        if (!isValidMessage(clientMessage)) {
            server->sendMessageToClient(curClient,"0");
            isClosingMessage = false; //We'll keep taking requests from user
            continue;
        }

        //Will handle user request, sending his/her
        //position back
        pthread_mutex_lock(&_lock);
        position = _timeRanking->insert(clientMessage);
        cout << position << endl;
        pthread_mutex_unlock(&_lock);
        server->sendMessageToClient(curClient,position);


        } while (!isClosingMessage);

    return NULL;

}