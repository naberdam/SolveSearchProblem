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
class BestFirstSearch : public SearcherByPriorityQueueByComparator<string, T, ComparatorByCost<T>> {

public:
    virtual string search(Searchable<T> *searchable) {
        this->addToOpenList(searchable->getInitializeState());
        while (this->getOpenListSize() > 0) {
            //start develop the node from openList
            State<T> *nodeFromOpenListWeNeedToHandle = this->popOpenList();
            this->addToCloseList(nodeFromOpenListWeNeedToHandle);
            //if we got to the goal
            if (*nodeFromOpenListWeNeedToHandle == *searchable->getGoalState()) {
                cout << nodeFromOpenListWeNeedToHandle->getCost() << endl;
                string result = this->backTrace(nodeFromOpenListWeNeedToHandle, searchable);
                this->deleteEverything();
                return result;
            }
            vector<State<T> *> neighboursOfNodeFromOpenLost = searchable->getPossibleNextStates(
                    *nodeFromOpenListWeNeedToHandle);
            for (auto neighbour : neighboursOfNodeFromOpenLost) {
                if (!this->doWeHaveThisNodeInClosedList(neighbour) && !this->doWeHaveThisNodeInOpenList(neighbour)) {
                    neighbour->setFather(nodeFromOpenListWeNeedToHandle);
                    this->addToOpenList(neighbour);
                } else if (this->doWeHaveThisNodeInClosedList(neighbour)) {
                    continue;
                } else {
                    this->updateStatePriority(neighbour);
                }
            }
        }
        this->deleteEverything();
        return this->noPathFromInitializeToGoal(searchable);
    }

    virtual ~BestFirstSearch() {

    }
};

#endif //UNTITLED2_BESTFIRSTSEARCH_H
