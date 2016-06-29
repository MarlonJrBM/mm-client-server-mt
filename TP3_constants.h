#ifndef TP3_CONSTANTS_H
#define TP3_CONSTANTS_H

/**
* TCP MT Client-Server solution to the Olympic Protocol Problem.
*/
namespace TP3 {

	/**
	* The DEBUG constant is set at compile-time. 
	* This constant dictates the logging behavior of the application.
	* True means everything will be logged, whereas false nothing will be logged.
	*/
	#ifdef DEBUG
	const bool LOGGING = true;
	#else
	const bool LOGGING = false;
	#endif

	const unsigned int TIMEOUT = 2; ///< Number of seconds client will wait for response
	const unsigned int MAX_NUM_TIMEOUTS = 10; ///< Number of timeouts before client finishes application.
	const unsigned int MAX_BUF = 101; ///< Maximum number of characters exchanged between server and client.
	const unsigned MAX_NUM_CONNECTIONS = 7; ///< Maximum number of connections server can take.

}








#endif