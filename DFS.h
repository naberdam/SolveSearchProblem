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
    //the first thing to do is to add the initializeState to openList
    this->addToOpenList(searchable->getInitializeState());
    //till openList is empty
    while (this->getOpenListSize() > 0) {
      //take the node from openList, so we will be able to work on him
      State<T> *nodeFromOpenListWeNeedToHandle = this->popOpenList();
      //if we got to the goal, so we call to backTrace which is in BackTraceSearcher
      if (*nodeFromOpenListWeNeedToHandle == *searchable->getGoalState()) {
        string result = this->backTrace(nodeFromOpenListWeNeedToHandle, searchable);
        this->deleteEverything();
        return result;
      }
      //if this node is not in closedList, so add it
      if (!this->doWeHaveThisNodeInClosedList(nodeFromOpenListWeNeedToHandle)) {
        this->addToCloseList(nodeFromOpenListWeNeedToHandle);
        //get vector of all relevant neighbours
        vector<State<T> *> neighboursOfNodeFromOpenLost = searchable->getPossibleNextStates(
            *nodeFromOpenListWeNeedToHandle);
        for (auto neighbour : neighboursOfNodeFromOpenLost) {
          if (!this->doWeHaveThisNodeInClosedList(neighbour) && !this->doWeHaveThisNodeInOpenList(neighbour)) {
            this->addToOpenList(neighbour);
          }
        }
      } else {
        delete nodeFromOpenListWeNeedToHandle;
      }
    }
    //we do not have a path from initializeState to goalState so we will send an appropriate message
    this->deleteEverything();
    return this->noPathFromInitializeToGoal(searchable);
  }

  virtual ~DFS() {}
};

#endif //UNTITLED2_DFS_H
