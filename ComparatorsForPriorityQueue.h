//
// Created by nerya on 14/01/2020.
//

#ifndef UNTITLED2_COMPARATORSFORPRIORITYQUEUE_H
#define UNTITLED2_COMPARATORSFORPRIORITYQUEUE_H

#include "State.h"

//comparator by cost for BestFirstSearch algorithm
template<class T>
class ComparatorByCost {
 public:
  bool operator()(State<T> *leftSide, State<T> *rightSide) {
    return leftSide->getCost() < rightSide->getCost();
  }
};

//comparator by heuristic for AStar algorithm
template<class T>
class ComparatorByHeuristic {
 public:
  bool operator()(State<T> *leftSide, State<T> *rightSide) {
    return (leftSide->getHeuristicDistance() + leftSide->getCost())
        < (rightSide->getHeuristicDistance() + rightSide->getCost());
  }
};

#endif //UNTITLED2_COMPARATORSFORPRIORITYQUEUE_H
