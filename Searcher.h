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
template <class Solution, class T>
class Searcher {
public:
    virtual Solution search(Searchable<T> *searchable) = 0;

    virtual unsigned long getNumberOfNodesEvaluated() = 0;

    virtual ~Searcher() {}
};

#endif //UNTITELD2_SEARCHER_H
