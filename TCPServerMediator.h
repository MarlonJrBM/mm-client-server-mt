#ifndef TCPServerMediator_H
#define TCPServerMediator_H

#include <iostream>
#include <cstdio>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>    
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>


namespace TP3{

/**
 * Mediator class used by the client to communicate with the server.
 * Assumes communication is entirely done via UDP. This class only treats
 * communication with ONE server. It also uses a stop-and-wait sliding window
 * to maintain communication reliability.
 */
class TCPServerMediator {
public:

	/**
	* Sets up socket and connect to server
	* Will take IPv4, IPv6 or regular domain names.
	* @param addr server address.
	* @param port port which will connect to.
	* @return newly created socket's ID
	*/
	int setUpSocket(const std::string& addr, unsigned port);

	/**
	* Closes connection with server and cleans up mediator inner structures
	* To be called once communication with server is done.
	*/
	void cleanUp();

	/**
	* Listens to a response for a certain amount of time.
	* @param timeout maximum amount of time (seconds) mediator will wait for a response in the network; defaults to zero (never times out).
	* @return message sent by server or "TIMEOUT" if timeout has been reached 
	*/
    std::string getResponse(unsigned timeout = 0);

    /**
    * Sends a message to the server.
    * @param message message to be sent.
    */
	void sendRequest(const std::string& message);



protected:

	int _serverSocketId; ///< ID of the socket used to communicate with the server.
    addrinfo* _result; /**< structure used to hold server address. */
};

} //namespace TP3

#endif
