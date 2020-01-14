//
// Created by amitai on 10/01/2020.
//

#ifndef UNTITELD2_SEARCHABLE_H
#define UNTITELD2_SEARCHABLE_H
#include "State.h"
#include <vector>
#include <string>

using namespace std;

//interface for a thing to search in it
//the functional of the search problem
template<class T>
class Searchable {
public:
    //get the initialize state - the source
    virtual State<T> *getInitializeState() = 0;

    //return the goal state - the detination state
    virtual State<T> *getGoalState() = 0;

    //return all the possible states - the structure in a vector
    virtual vector<State<T>*> getPossibleNextStates(State<T> &current) = 0;
};

#endif //UNTITELD2_SEARCHABLE_H
