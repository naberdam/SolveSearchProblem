//
// Created by nerya on 14/01/2020.
//

#ifndef UNTITLED2_DFS_H
#define UNTITLED2_DFS_H

#include "SearcherByStack.h"

template<class T>
class DFS : public SearcherByStack<string, T> {
public:
    virtual string search(Searchable<T> *searchable) {
        this->addToOpenList(searchable->getInitializeState());
        //as long there is a node in the queue
        while (this->getOpenListSize() > 0) {
            State<T> *nodeFromOpenListWeNeedToHandle = this->popOpenList();
            if (*nodeFromOpenListWeNeedToHandle == *searchable->getGoalState()) {
                cout << nodeFromOpenListWeNeedToHandle->getCost() << endl;
                string result = this->backTrace(nodeFromOpenListWeNeedToHandle, searchable);
                this->deleteEverything();
                return result;
            }
            if (!this->doWeHaveThisNodeInClosedList(nodeFromOpenListWeNeedToHandle)) {
                this->addToCloseList(nodeFromOpenListWeNeedToHandle);
            }
            vector<State<T> *> neighboursOfNodeFromOpenLost = searchable->getPossibleNextStates(
                    *nodeFromOpenListWeNeedToHandle);
            for (auto neighbour : neighboursOfNodeFromOpenLost) {
                if (!this->doWeHaveThisNodeInClosedList(neighbour) && !this->doWeHaveThisNodeInOpenList(neighbour)) {
                    this->addToOpenList(neighbour);
                }
            }
        }
        this->deleteEverything();
        return this->noPathFromInitializeToGoal(searchable);
    }
};

#endif //UNTITLED2_DFS_H
