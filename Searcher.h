//
// Created by amitai on 10/01/2020.
//

#ifndef UNTITELD2_SEARCHER_H
#define UNTITELD2_SEARCHER_H

#include <iostream>
#include <queue>
#include "Solver.h"
#include "Searchable.h"

//interface for all the methods of searcher
template<class T>
class Searcher {
protected:
    int costOfAllNodes = 0;
    int nodesNumer = 0;
public:
    //method for the search function - search in the searchable
    //update the number of nodes and return string of the path
    //absrtact - because need to be implemented in every one differnetly

    virtual string search(Searchable<T> *searchable) = 0;

    //return the total cost of all the nodes in the path -
    // all the nodes evaluated
    virtual int getCostOfNodes() {
        return this->costOfAllNodes;
    };

//get the numebr of nodes
    //virtual int numberOFNodes() {
    //get the numebr of nodes
    virtual int numberOFNodes() {
        return this->nodesNumer;
    };
};

#endif //UNTITELD2_SEARCHER_H
