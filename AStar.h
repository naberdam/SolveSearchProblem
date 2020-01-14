//
// Created by nerya on 14/01/2020.
//

#ifndef UNTITLED2_ASTAR_H
#define UNTITLED2_ASTAR_H

#include "SearcherByPriorityQueue.h"

using namespace std;

template<class T>
class AStar : public SearcherByPriorityQueue<string, T> {
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
            vector<State<T> *> neighboursOfNodeFromOpenLost = searchable->getPossibleNextStatesWithManhattan(
                    *nodeFromOpenListWeNeedToHandle, *searchable->getGoalState());
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
};


#endif //UNTITLED2_ASTAR_H
