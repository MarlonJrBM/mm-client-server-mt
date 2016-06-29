#ifndef RANKING_H
#define RANKING_H

#include <set>
#include <string>

namespace TP3 {

/**
* Container for athletes times in the Olympic Protocol.
* This class is responsible for keeping times performed by the
* athletes in the Olympic Protocol, in addition to their respective
* position in the race.
*/
class Ranking {

public:
    /** 
    * Inserts time into ranking and returns the associated position.
    * @param s string with the corresponding time (in h:m:s:ms format)
    * @return the athtlete's position.
    */
    std::string insert(const std::string& s);

    /**
    * Clears time container.
    * This method erases all times currently registered.
    */
    void clear();

protected:
    std::multiset<unsigned long long> _rankingContainer; ///< internal structure used to store the times.

    /**
    * Helper function to convert time to miliseconds.
    * This method converts from the (h:m:s:ms) format to ms.
    * @param message time in (h:m:s:ms) format.
    * @return time in miliseconds.
    */
    unsigned long long convertMessageToTime(std::string message);
};

} //namespace TP3

#endif
