#ifndef CLIENTAPPLICATION_H
#define CLIENTAPPLICATION_H

#include "TCPServerMediator.h"
#include <cstdio>
#include <iostream>

namespace TP3{

/**
* Encapsulates business logic and user interface of the client application.
* This class is responsible for collecting user input (stdin) and displaying
* information to the user on the screen (stdout).
*/
class ClientApplication {

public:
	/**
	* Entry point of the application.
	* This is the entry point of the application. Most likely called from main().
	* Implements stop-and-wait protocol in order to communicate with server.
	* @param argc number of arguments.
	* @param argv command line arguments.
	* @return return code of the entire program
	*/
	int runApplication(int argc,char** argv);

protected:
	TCPServerMediator _mediator; /**< used by the client to comunicate with server. */

	/**
	* Gets client input from standard input (entire line).
	* @return message provided by user in standard input.
	*/
	std::string getClientInput();

	/**
	* Displays information on user screen (standard output).
	* @param message message to be displayed.
	*/ 
	void displayResponse(const std::string& message);


	/**
	* Does basic client-side input verification.
	* @param message message to be verified.
	* @return true if message is valid.
	*/
	bool isValidMessage(const std::string& message);

};

} //namespace TP3







#endif
