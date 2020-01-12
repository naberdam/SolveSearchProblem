//
// Created by amitai on 10/01/2020.
//

#ifndef UNTITELD2_SEARCHABLE_H
#define UNTITELD2_SEARCHABLE_H
#include "State.h"
#include <vector>
#include <string>
#include <list>

using namespace std;

//interface for a thing to search in it
//the functional of the search problem
template<class T>
class Searchable {
public:
    //get the initialize state - the source
    /*virtual*/ State<T> *getInitializeState();

    //return the goal state - the detination state
    virtual State<T> *getGoalState() = 0;

    //return all the structure of the searchable
    /*virtual*/ vector<State<T> *> getStructure();

    //return all the possible states - the structure in a vector
    virtual std::__cxx11::list<State<struct Point *> *> * getAllPossibleStates(State<T> *currentState) = 0;

    //update the searchable that we want
    /*virtual*/ void setStructure(vector<State<T> *> structure) ;

    //set the initial state of the searchable item
    /*virtual*/ void setInitialState(State<T> *initialState);

    //set the goal state of the searchable item
    /*virtual*/ void setGoalState(State<T> *goalState);

    //get the huristic from start to goal
    virtual double getHuristic(State<T> * start,State<T>* goal){

    };

    /*virtual*/ string getRoute();

    //todo - check if need pointer to vector
};

#endif //UNTITELD2_SEARCHABLE_H
