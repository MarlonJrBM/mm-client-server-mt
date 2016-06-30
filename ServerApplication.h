#ifndef SERVER_APPLICATION_H
#define SERVER_APPLICATION_H

#include <pthread.h>
#include <vector>
#include "Ranking.h"

namespace TP3 {

/**
* Encapsulates server's business logic
* This class is responsible for connecting the server-side concerns with the athtletes ranking concern.
*/
class ServerApplication {

public:
    /**
	* Entry point of the application.
	* This is the entry point of the application and contains its main loop.
	* Implements stop-and-wait protocol in order to communicate with client.
	* @param argc number of arguments.
	* @param argv command line arguments.
	* @return return code of the entire program
	*/
    int runApplication(int argc, char** argv);

    /*
    * Function which will process a new client function.
    * A new thread should be opened each time the function is called.
    * @param clientId
    */
    static void* processClient(void* clientData);

    /**
    * Cleans up server singleton.
    */
    ~ServerApplication();

protected:
    static Ranking* _timeRanking; ///< keeps storage of times sent by client (athletes).
    std::vector<pthread_t> _tidList;
    std::vector<unsigned> _clientList;
    static pthread_mutex_t _lock;
    unsigned _numClients; ///< number of currently connected clients. 

    /**
    * Checks whether message is a closing signal.
    * A closing signal is a negative number which the client sends.
    * @param message client message.
    * @return true if it's closing signal.
    */
    static bool isClosingSignal(const std::string& message);

    /**
    * Checks whether message is a valid one.
    * A valid message is a message which starts with a digit.
    * @param message client message.
    * @return true if it's valid message
    */
    static bool isValidMessage(const std::string& message);
	
};


} //namespace TP3

#endif
