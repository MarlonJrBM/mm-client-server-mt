#include "ServerApplication.h"

#include <iostream>

#include "TCPMTServer.h"
#include "Ranking.h"
#include "TP3_constants.h"

using namespace std;
using namespace TP3;


TCPMTServer* TCPMTServer::_serverInstance = NULL;

int ServerApplication::runApplication(int argc, char** argv) {

    //Local and helper variables
    int curClient = -1;
    string clientMessage = "";
    string position = "";
    string port = argv[1];
    bool isClosingMessage = false;
    
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
        //Client connects and send their time in the race
        curClient = server->acceptClient(); 

        do {
            clientMessage = server->getMessageFromClient(curClient);
            isClosingMessage = isClosingSignal(clientMessage);

            if (isClosingMessage) {
                _timeRanking->clear();
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
            position = _timeRanking->insert(clientMessage);
            cout << position << endl;
            server->sendMessageToClient(curClient,position);


        } while (!isClosingMessage);

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
}

