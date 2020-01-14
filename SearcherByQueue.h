//
// Created by nerya on 14/01/2020.
//

#ifndef UNTITLED2_SEARCHERBYQUEUE_H
#define UNTITLED2_SEARCHERBYQUEUE_H

#include "BackTraceSearcher.h"
#include <vector>

template <class Solution, class T>
class SearcherByQueue : public BackTraceSearcher<Solution, T> {
public:

    queue<State<T>*> openList;
    /*unordered_set<State<T>*> closedList;*/
    vector<State<T>*> closedList;

    State<T> *popOpenList() {
        this->increaseNumberOfNodesEvaluated();
        State<T> *result = openList.front();
        openList.pop();
        return result;
    }
    unsigned long getOpenListSize() {
        return openList.size();
    }

    void addToOpenList(State<T> *current) {
        openList.push(current);
    }

    void addToCloseList(State<T> *current) {
        closedList.push_back(current);
    }

    bool doWeHaveThisNodeInClosedList(State<T> *current) {
        for (auto node : closedList) {
            if (*current == *node) {
                return true;
            }
        }
        return false;
    }

    vector<State<T>*> vectorOfOpenList() {
        vector<State<T>*> openListVector;
        while (!openList.empty()) {
            openListVector.push_back(openList.front());
            openList.pop();
        }
        for (auto item : openListVector) {
            openList.push(item);
        }
        return openListVector;
    }

    bool doWeHaveThisNodeInOpenList(State<T> *current) {
        vector<State<T>*> openListVector = vectorOfOpenList();
        for (auto item : openListVector) {
            if (*current == *item) {
                return true;
            }
        }
        return false;
    }

    void deleteEverything() {
        while (!openList.empty()) {
            auto item = openList.front();
            openList.pop();
            delete item;
        }
        closedList.clear();
    }


public:

    virtual Solution search(Searchable<T> *searchable) = 0;

    virtual ~SearcherByQueue() {}
};

#endif //UNTITLED2_SEARCHERBYQUEUE_H
