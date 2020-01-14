//
// Created by nerya on 13/01/2020.
//

#ifndef UNTITLED2_MYSEARCHER_H
#define UNTITLED2_MYSEARCHER_H

#include "Searcher.h"
#include <stack>
template <class Solution, class T>

class MySearcher : public Searcher<Solution, T> {
private:
    unsigned long evaluatedNodes;

protected:

    string backTrace(State<T> *current, Searchable<T> *searchable) {
        stack<State<T> *> trace;
        State<T> *tempState = current;
        string result = "";

        while (!(*tempState == *searchable->getInitializeState())) {
            trace.push(tempState);
            tempState = tempState->getFather();
        }
        trace.push(searchable->getInitializeState());

        while (!trace.empty()) {
            State<T>* item = trace.top();
            switch (item->getDirection()) {
                case UP:
                    result += "up,";
                    break;
                case DOWN:
                    result += "down,";
                    break;
                case LEFT:
                    result += "left,";
                    break;
                case RIGHT:
                    result += "right,";
                    break;
                default:
                    break;
            }
            trace.pop();
        }
        result.pop_back();
        return result;
    }

    virtual void increaseNumberOfNodesEvaluated() {
        ++evaluatedNodes;
    }

public:
    MySearcher() : evaluatedNodes(0) {}

    virtual Solution search(Searchable<T> *searchable) = 0;

    virtual unsigned long getNumberOfNodesEvaluated() {
        return evaluatedNodes;
    }

    virtual ~MySearcher() {}


};

#endif //UNTITLED2_MYSEARCHER_H
