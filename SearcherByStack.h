//
// Created by nerya on 14/01/2020.
//

#ifndef UNTITLED2_SEARCHERBYSTACK_H
#define UNTITLED2_SEARCHERBYSTACK_H

#include "BackTraceSearcher.h"

template<class Solution, class T>
class SearcherByStack : public BackTraceSearcher<Solution, T> {

protected:
public:
    virtual ~SearcherByStack() {

    }

protected:
    stack<State<T> *> openList;
    vector<State<T> *> closedList;

    virtual State<T> *popOpenList() {
        this->increaseNumberOfNodesEvaluated();
        State<T> *result = openList.top();
        openList.pop();
        return result;
    }

    virtual unsigned long getOpenListSize() {
        return openList.size();
    }

    virtual void addToOpenList(State<T> *current) {
        openList.push(current);
    }

    virtual void addToCloseList(State<T> *current) {
        closedList.push_back(current);
    }

    virtual bool doWeHaveThisNodeInOpenList(State<T> *current) {
        bool isFound = false;
        stack<State<T> *> temp;
        while (!openList.empty()) {
            if (*openList.top() == *current) {
                isFound = true;
                break;
            }
            temp.push(openList.top());
            openList.pop();
        }
        while (!temp.empty()) {
            openList.push(temp.top());
            temp.pop();
        }
        return isFound;
    }

    virtual bool doWeHaveThisNodeInClosedList(State<T> *current) {
        for (auto node : closedList) {
            if (*current == *node) {
                return true;
            }
        }
        return false;
    }

    virtual void deleteEverything() {
        while (!openList.empty()) {
            auto item = openList.top();
            openList.pop();
            delete item;
        }
        closedList.clear();
    }


public:

    virtual Solution search(Searchable<T> *searchable) = 0;

};


#endif //UNTITLED2_SEARCHERBYSTACK_H
