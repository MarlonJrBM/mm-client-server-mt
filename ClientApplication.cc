#include "ClientApplication.h"

#include <iostream>
#include <cstdio>
#include <string>
#include <regex>

#include "TP3_constants.h"

using namespace std;
using namespace TP3;


/******************************************************************************
 * Client's application main loop. Messages are verified in a stop-and-wait
 * fashion.
 *******************************************************************************/
int ClientApplication::runApplication(int argc, char** argv) {
	string clientMessage = "";
	string serverResponse = "";
	long long convertedTime = 0;
    string addr = argv[1];
    string port = argv[2];
    int connectionFlag = -1;

	if (LOGGING) cout << "Starting Client Application" << endl;
    if (LOGGING) cout << "Number of arguments: " << argc << endl;
    
	connectionFlag = _mediator.setUpSocket(addr.c_str(), stoul(port));
    if (connectionFlag < 0 ) {
        cout << "ERROR! Could not open socket " << addr <<  ":" << port << endl;
        exit(1);
    }

	do {
		clientMessage = getClientInput();

		//This does basic client-side input verification
		//If user doesn't send a valid time, it won't be sent
		//to server
		if (isValidMessage(clientMessage)) { 
			convertedTime = stoll(clientMessage);
		} else {
			cout << "Invalid message!" << endl; 
			convertedTime = 0;
			continue;
		}

		//sends converted time to server
		_mediator.sendRequest(clientMessage);

		serverResponse = _mediator.getResponse();

		displayResponse(serverResponse);

	} while (convertedTime >= 0);

	_mediator.cleanUp();

	return 0;
}

void ClientApplication::displayResponse(const string& message) {

    if (stoll(message) >= 0) {
	    cout << message << endl;
    } else {
        //Server is ending connection
        if (LOGGING) {
            cout << "Exiting client" << endl;
        }
    }
}

string ClientApplication::getClientInput() {
	string clientMessage;
	if (LOGGING) {
		cout << "Please type your time" << endl;
	}
	getline(cin, clientMessage);
	return clientMessage;
}

/******************************************************************************
* A valid message is a message which starts with a digit
*******************************************************************************/
bool ClientApplication::isValidMessage(const string& message) {
	return strtoll(message.c_str(), NULL, 10);
}
