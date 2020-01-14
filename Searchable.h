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
    // get the start of the way
    virtual State<T> *getInitializeState() = 0;

    //return the goal state of the way
    virtual State<T> *getGoalState() = 0;

    // return all of the possible place that we can go to them
    virtual vector<State<T> *> getPossibleNextStates(State<T> &current) = 0;

    // return all of the possible states for the huristic
    virtual vector<State<T> *> getPossibleNextStatesWithManhattan(State<T> &current, State<T> &goal) = 0;

    virtual ~Searchable();
};

template<class T>
Searchable<T>::~Searchable() {

}

#endif //UNTITELD2_SEARCHABLE_H
