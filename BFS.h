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
            vector<State<T>*> neighboursOfNodeFromOpenLost = searchable->getPossibleNextStates(*nodeFromOpenListWeNeedToHandle);
            for (auto neighbour : neighboursOfNodeFromOpenLost) {
                if (!this->doWeHaveThisNodeInClosedList(neighbour)) {
                    this->addToOpenList(neighbour);
                    this->addToCloseList(neighbour);
                }
            }
        }
        this->deleteEverything();
        return this->noPathFromInitializeToGoal(searchable);
    }

    virtual ~BFS() {

    }
};


#endif //UNTITLED2_BFS_H
