//
// Created by nerya on 14/01/2020.
//

#ifndef UNTITLED2_BFS_H
#define UNTITLED2_BFS_H

#include "SearcherByQueue.h"
#include "Point.h"

template <class T>
class BFS : public SearcherByQueue<string, T>{
public:
    virtual string search(Searchable<Point> *searchable) {
        //the first thing to do is to add the initializeState to openList
        this->addToOpenList(searchable->getInitializeState());
        //till openList is empty
        while (this->getOpenListSize() > 0) {
            //take the node from openList, so we will be able to work on him
            State<T> *nodeFromOpenListWeNeedToHandle = this->popOpenList();
            //if we got to the goal, so we call to backTrace which is in BackTraceSearcher
            if (*nodeFromOpenListWeNeedToHandle == *searchable->getGoalState()) {
                cout << nodeFromOpenListWeNeedToHandle->getCost() << endl;
                string result = this->backTrace(nodeFromOpenListWeNeedToHandle, searchable);
                this->deleteEverything();
                return result;
            }
            //get vector of all relevant neighbours
            vector<State<T>*> neighboursOfNodeFromOpenLost = searchable->getPossibleNextStates(*nodeFromOpenListWeNeedToHandle);
            for (auto neighbour : neighboursOfNodeFromOpenLost) {
                if (!this->doWeHaveThisNodeInClosedList(neighbour)) {
                    this->addToOpenList(neighbour);
                    this->addToCloseList(neighbour);
                }
            }
        }
        //we do not have a path from initializeState to goalState so we will send an appropriate message
        this->deleteEverything();
        return this->noPathFromInitializeToGoal(searchable);
    }

    virtual ~BFS() {

    }
};


#endif //UNTITLED2_BFS_H
