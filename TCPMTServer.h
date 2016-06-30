#ifndef TCPMT_SERVER_H
#define TCPMT_SERVER_H

#include <iostream>
#include <vector>
#include <cstdio>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>



namespace TP3 {

/**
* TCP-MT Server counterpart to the Olympic Protocol problem. 
* This server sends back the position performed by athletes (client)
* in a MT manner. Will take many clints at a time in a THREAD-SAFE manner.
*/
class TCPMTServer {
    
    public:
       
        /**
        * Gets server's singleton instance.
        * Instantiates server in a lazy manner if needed.
        * @return pointer to server instance.
        */
        static TCPMTServer* getInstance() {
            if (_serverInstance == NULL) {
                _serverInstance = new TCPMTServer();
            }
            return _serverInstance;
        }

        /**
        * Deletes server's singleton and cleans its internal structures if needed.
        */ 
        static void deleteInstance() {
            if (_serverInstance->_serverSocketId != -1) {
                close(_serverInstance->_serverSocketId);
            }
            
            if (_serverInstance != NULL) {
                delete _serverInstance;
            }
        }

        /**
        * Binds TCPMTServer to specified port.
        * @param port
        */
        void setUp(const std::string& port);

        void run(); ///< UNIMPLEMENTED

        void stop(); ///< UNIMPLEMENTED
        

        /**
        * Accepts a client via TCP.
        * This is a blocking call which blocks until a new client is accepted
        * @return id referring to accepted client.
        */
        int acceptClient();

        /**
        * Sends message to client.
        * @param clientId
        * @param message
        */
        void sendMessageToClient(int clientId, const std::string& message);

        /**
        * Obtains string from a TCP packet in the network from a certain client.
        * @param clientId
        * @return client message.
        */ 
        std::string getMessageFromClient(int clientId);

        /**
        * Sends closing signal to client (-1).
        * @param clientId
        */
        void closeConnection(int clientId);

    
    protected:
        static TCPMTServer* _serverInstance; ///< server's singleton instance.
        TCPMTServer() {}; ///< private constructor since this is a singleton class.
        sockaddr_in6 _serverSocket; ///< strucutre which holds server socket data.
        int _serverSocketId; ///< ID of the socket used to communicate with the client.      

};

} //namespace

#endif

