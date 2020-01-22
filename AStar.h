//
// Created by nerya on 14/01/2020.
//

#ifndef UNTITLED2_ASTAR_H
#define UNTITLED2_ASTAR_H

#include "SearcherByPriorityQueueByComparator.h"

using namespace std;

template<class T>
class AStar : public SearcherByPriorityQueueByComparator<string, T, ComparatorByHeuristic<T>> {
 public:

  virtual string search(Searchable<T> *searchable) {
    searchable->getInitializeState()->setHeuristicDistance(searchable->setHeuristicForNode(*searchable->getInitializeState(),
                                                                                           *searchable->getGoalState()));
    this->addToOpenList(searchable->getInitializeState());
    while (this->getOpenListSize() > 0) {
      //start develop the node from openList
      State<T> *nodeFromOpenListWeNeedToHandle = this->popOpenList();
      this->addToCloseList(nodeFromOpenListWeNeedToHandle);
      //if we got to the goal
      if (*nodeFromOpenListWeNeedToHandle == *searchable->getGoalState()) {
        string result = this->backTrace(nodeFromOpenListWeNeedToHandle, searchable);
        this->deleteEverything();
        return result;
      }
      vector<State<T> *>
          neighboursOfNodeFromOpenLost = searchable->getPossibleNextStates(*nodeFromOpenListWeNeedToHandle);
      for (State<T> *neighbour : neighboursOfNodeFromOpenLost) {
        if (!this->doWeHaveThisNodeInClosedList(neighbour) && !this->doWeHaveThisNodeInOpenList(neighbour)) {
          neighbour->setHeuristicDistance(searchable->setHeuristicForNode(*neighbour, *searchable->getGoalState()));
          neighbour->setFather(nodeFromOpenListWeNeedToHandle);
          this->addToOpenList(neighbour);
        } else if (this->doWeHaveThisNodeInClosedList(neighbour)) {
          continue;
        } else {
          neighbour->setHeuristicDistance(searchable->setHeuristicForNode(*neighbour, *searchable->getGoalState()));
          neighbour->setFather(nodeFromOpenListWeNeedToHandle);
          this->updateStatePriority(neighbour);
        }
      }
    }
    this->deleteEverything();
    return this->noPathFromInitializeToGoal(searchable);
  }

  virtual ~AStar() {}
};

#endif //UNTITLED2_ASTAR_H
