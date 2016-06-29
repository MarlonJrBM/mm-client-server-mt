#include "Ranking.h"

#include <iostream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <algorithm>

#include "ServerApplication.h"
#include "TP3_constants.h"

using namespace std;
using namespace TP3;


void Ranking::clear() {
    if (LOGGING) {
        cout << "Clearing ranking" << endl;
    }
    _rankingContainer.clear();
}


string Ranking::insert(const string& s) {

    if (LOGGING) {
        cout << "Inserting message into ranking" << endl;
    }

    multiset<unsigned long long>::iterator it;
    unsigned int position = 0;

    //Converts string to unsigned...
    //Assumes it's safe!
    unsigned long long raceTime = convertMessageToTime(s);
    
    //keeps position of newly inserted element
    it = _rankingContainer.insert(raceTime);

    //clever trick to retrieve the position:
    //subtract the new element from beginning
    position =  distance(_rankingContainer.begin(), it);

    //Adds 1 because positions start at 1 (not 0)
    return  to_string(position+1);

}


unsigned long long Ranking::convertMessageToTime(string message) {

    //Local and helper variables
    int numHours = 0, numMinutes = 0, numSeconds = 0, numMiliSeconds = 0, number = 0;
    string numberStr = "";
    char c;
    bool warningFlag = true;

    //Removes ALL whitespaces
    message.erase(remove_if(message.begin(),message.end(),[](char x){return std::isspace(x);}), message.end());

    for (unsigned ii=0; ii< message.size();++ii) {
        c = message[ii];

        if (isdigit(c)) { 

            numberStr.append(1, c);

        } else {
            if (warningFlag) warningFlag = false;

            number = stoi(numberStr);
            numberStr.clear();

            switch (c) { /* now we grab the letter right after the number */
                case 'h':
                case 'H':
                    numHours = number;
                    break;

                case 's':
                case 'S':
                    numSeconds = number;
                    break;

                case 'm':
                case 'M':
                    if (ii == (message.size() - 1) || tolower(message[ii+1]) != 's') { 
                        /* minutes case, because this is last character or the next character is not an s */
                        numMinutes = number;
                    } else { /* miliseconds case, because next character it's an s) */
                        numMiliSeconds = number;
                        ii++;      
                    }
                    break;
            }
        } 
    }

    if (warningFlag) {
        cout << "WARNING: Something is wrong with input but I'm taking it anyway..." << endl;
    }

    return (numHours * 3600000ULL) + (numMinutes * 60000ULL) + (numSeconds * 1000ULL) + (numMiliSeconds);

}

//Given message string, will return time in MILLISECONDS
// unsigned long long Ranking::convertMessageToTime(string message) {

//     //Local and helper variables
//     int numHours = 0, numMinutes = 0, numSeconds = 0, numMiliSeconds = 0, number = 0;
//     size_t index = 0;
//     string word = "";

//     vector<string> words = getWordsFromString(message);

//     //Iterates through each word, extracting possible values
//     for (unsigned ii=0; ii<words.size();++ii) {
//         word = words[ii];

//         //The below function WILL BREAK THE PROGRAM is user provides wrong input
//         number = stoi(word, &index); /* index will store the amount of characters processed */

//         //Input doesn't have time identifier right after it...
//         if (word.size() < index+1) {

//             //There are no more words, we'll just return the number
//             if (ii == words.size() - 1) {
//                 cout << "WARNING: Something is wrong with input but I'm taking it anyway..." << endl;
//                 return number;
//             }

//             //Is the next word a letter?
//             word = words[++ii];
//             if (isalpha(word[0])) {

//                 //Good,we'll keep a reference to it in the word and index variable and use it in the below
//                 //switch
//                 index = 0;
//             } else {

//                 //If it isn't we'll just return the number again
//                 cout << "WARNING: Something is wrong with input but I'm taking it anyway..." << endl;
//                 return number;
//             }
//         }

//         switch (word[index]) { /* now we grab the letter right after the number */
//             case 'h':
//             case 'H':
//                 numHours = number;
//                 break;

//             case 's':
//             case 'S':
//                 numSeconds = number;
//                 break;

//             case 'm':
//             case 'M':
//                 if (word.size() < ++index + 1) { /* minutes case, because this is last character */
//                     numMinutes = number;
//                 } else { /* miliseconds case, because we still have one character left (assumes it's an s)) */
//                     numMiliSeconds = number;    
//                 }
//                 break;
//         }
//     }

//     //Returns value in miliseconds

//     return (numHours * 3600000ULL) + (numMinutes * 60000ULL) + (numSeconds * 1000ULL) + (numMiliSeconds);
// }