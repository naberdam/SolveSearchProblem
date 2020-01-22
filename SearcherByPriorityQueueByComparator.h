//
// Created by nerya on 13/01/2020.
//

#ifndef UNTITLED2_SEARCHERBYPRIORITYQUEUEBYCOMPARATOR_H
#define UNTITLED2_SEARCHERBYPRIORITYQUEUEBYCOMPARATOR_H

#include "BackTraceSearcher.h"
#include "ComparatorsForPriorityQueue.h"
#include <set>

template<class Solution, class T, class ComparatorToPriority>
class SearcherByPriorityQueueByComparator : public BackTraceSearcher<Solution, T> {
 protected:

  //multiset that used as priority queue and it has generic comparator
  //according the algorithm that use this class
  multiset<State<T> *, ComparatorToPriority> openList;
  vector<State<T> *> closedList;

  //pop from openList and update the multiset by using the comparator
  virtual State<T> *popOpenList() {
    this->increaseNumberOfNodesEvaluated();
    auto iter = openList.begin();
    State<T> *result = *iter;
    multiset < State<T> * , ComparatorToPriority > openListTemp;
    bool firstTime = true;
    for (auto i : openList) {
      //we have current in openList
      if (firstTime) {
        firstTime = false;
        continue;
      } else {
        openListTemp.insert(i);
      }
    }
    openList = openListTemp;
    return result;
  }

  virtual unsigned long getOpenListSize() {
    return openList.size();
  }

  virtual void addToOpenList(State<T> *current) {
    openList.insert(current);
  }

  virtual void addToCloseList(State<T> *current) {
    closedList.push_back(current);
  }

  //check if we have current in openList
  virtual bool doWeHaveThisNodeInOpenList(State<T> *current) {
    for (auto item : openList) {
      //we have current in openList
      if (*current == *item) {
        return true;
      }
    }
    //we do not have current in openList
    return false;
  }

  //check if we have current in closedList
  virtual bool doWeHaveThisNodeInClosedList(State<T> *current) {
    for (auto node : closedList) {
      if (*current == *node) {
        return true;
      }
    }
    return false;
  }

  //update cost item that is in openList if his cost is bigger than cost of current
  void updateCostItemInOpenList(State<T> *item, State<T> *current) {
    if (item->getCost() > current->getCost()) {
      multiset < State<T> * , ComparatorToPriority > openListTemp;
      /*auto i = openList.begin();
      auto end = openList.end();*/
      for (auto i : openList) {
        //we have current in openList
        if (*i == *item) {
          openListTemp.insert(current);
        } else {
          openListTemp.insert(i);
        }
      }
      /*openList.erase(item);*/
      delete item;
      openList = openListTemp;
      /*openList.insert(current);*/
    }
  }

  //update openList - add current to the list or update his cost in openList if there it is needed
  void updateStatePriority(State<T> *current) {
    bool wasFound = false;
    for (auto item : openList) {
      if (*item == *current) {
        wasFound = true;
        updateCostItemInOpenList(item, current);
        break;
      }
    }
    if (!wasFound) {
      openList.insert(current);
    }
  }

  virtual void deleteEverything() {
    openList.clear();
    closedList.clear();
  }

 public:
  virtual Solution search(Searchable<T> *searchable) = 0;

  virtual ~SearcherByPriorityQueueByComparator() {}
};

#endif //UNTITLED2_SEARCHERBYPRIORITYQUEUEBYCOMPARATOR_H
