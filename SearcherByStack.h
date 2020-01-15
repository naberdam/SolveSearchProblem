//
// Created by nerya on 14/01/2020.
//

#ifndef UNTITLED2_SEARCHERBYSTACK_H
#define UNTITLED2_SEARCHERBYSTACK_H

#include "BackTraceSearcher.h"

template<class Solution, class T>
class SearcherByStack : public BackTraceSearcher<Solution, T> {

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

    //check if we have current in openList
    virtual bool doWeHaveThisNodeInOpenList(State<T> *current) {
        bool isFound = false;
        //temp is the opposite of openList
        stack<State<T> *> temp;
        while (!openList.empty()) {
            if (*openList.top() == *current) {
                isFound = true;
                break;
            }
            temp.push(openList.top());
            openList.pop();
        }
        //return openList to its normal state
        while (!temp.empty()) {
            openList.push(temp.top());
            temp.pop();
        }
        return isFound;
    }

    virtual bool doWeHaveThisNodeInClosedList(State<T> *current) {
        //check if we have current in openList
        for (auto item : closedList) {
            //we have current in openList
            if (*current == *item) {
                return true;
            }
        }
        //we do not have current in openList
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

    virtual ~SearcherByStack() {}

};


#endif //UNTITLED2_SEARCHERBYSTACK_H
