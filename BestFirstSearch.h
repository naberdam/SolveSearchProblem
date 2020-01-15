//
// Created by amitai on 09/01/2020.
//


#ifndef UNTITLED2_BESTFIRSTSEARCH_H
#define UNTITLED2_BESTFIRSTSEARCH_H

#include "SearcherByPriorityQueueByComparator.h"
#include <queue>
#include <vector>

using namespace std;

template<class T>
//we want that the priority queue will be set by cost and that is why we give ComparatorByCost to him
class BestFirstSearch : public SearcherByPriorityQueueByComparator<string, T, ComparatorByCost<T>> {

public:
    virtual string search(Searchable<T> *searchable) {
        //the first thing to do is to add the initializeState to openList
        this->addToOpenList(searchable->getInitializeState());
        //till openList is empty
        while (this->getOpenListSize() > 0) {
            //take the node from openList, so we will be able to work on him
            State<T> *nodeFromOpenListWeNeedToHandle = this->popOpenList();
            //add to the closeList, because if it is in the top of the openList so it will has
            //the lowest cost between all the other nodes in openList for sure
            this->addToCloseList(nodeFromOpenListWeNeedToHandle);
            //if we got to the goal, so we call to backTrace which is in BackTraceSearcher
            if (*nodeFromOpenListWeNeedToHandle == *searchable->getGoalState()) {
                cout << nodeFromOpenListWeNeedToHandle->getCost() << endl;
                string result = this->backTrace(nodeFromOpenListWeNeedToHandle, searchable);
                this->deleteEverything();
                return result;
            }
            //get vector of all relevant neighbours
            vector<State<T> *> neighboursOfNodeFromOpenLost = searchable->getPossibleNextStates(
                    *nodeFromOpenListWeNeedToHandle);
            for (auto neighbour : neighboursOfNodeFromOpenLost) {
                if (!this->doWeHaveThisNodeInClosedList(neighbour) && !this->doWeHaveThisNodeInOpenList(neighbour)) {
                    /*neighbour->setFather(nodeFromOpenListWeNeedToHandle);*/
                    this->addToOpenList(neighbour);
                } else if (this->doWeHaveThisNodeInClosedList(neighbour)) {
                    continue;
                } else {
                    //if we have this neighbour in openList, so we need to check his cost and maybe
                    //to update it if the cost of neighbour is lower then the node we
                    //already have in openList
                    this->updateStatePriority(neighbour);
                }
            }
        }
        //we do not have a path from initializeState to goalState so we will send an appropriate message
        this->deleteEverything();
        return this->noPathFromInitializeToGoal(searchable);
    }

    virtual ~BestFirstSearch() {

    }
};

#endif //UNTITLED2_BESTFIRSTSEARCH_H
