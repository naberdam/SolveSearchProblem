//
// Created by nerya on 13/01/2020.
//

#ifndef UNTITLED2_BACKTRACESEARCHER_H
#define UNTITLED2_BACKTRACESEARCHER_H


#include "Searcher.h"
#include <stack>
template <class Solution, class T>

class BackTraceSearcher : public Searcher<Solution, T> {
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
                    result += "Up,";
                    break;
                case DOWN:
                    result += "Down,";
                    break;
                case LEFT:
                    result += "Left,";
                    break;
                case RIGHT:
                    result += "Right,";
                    break;
                default:
                    break;
            }
            trace.pop();
        }
        result.pop_back();
        return result;
    }

    virtual string noPathFromInitializeToGoal(Searchable<T> *searchable) {
        string msgToServerWithNoPath;
        msgToServerWithNoPath += "there is not trace from (";
        msgToServerWithNoPath += searchable->getInitializeState()->getState().getX();
        msgToServerWithNoPath += searchable->getInitializeState()->getState().getY();
        msgToServerWithNoPath += ") to (";
        msgToServerWithNoPath += searchable->getGoalState()->getState().getX();
        msgToServerWithNoPath += searchable->getGoalState()->getState().getY();
        msgToServerWithNoPath += ")";
        return msgToServerWithNoPath;
    }

    virtual void increaseNumberOfNodesEvaluated() {
        ++evaluatedNodes;
    }

public:
    BackTraceSearcher() : evaluatedNodes(0) {}

    virtual Solution search(Searchable<T> *searchable) = 0;

    virtual unsigned long getNumberOfNodesEvaluated() {
        return evaluatedNodes;
    }

    virtual ~BackTraceSearcher() {}


};

#endif //UNTITLED2_BACKTRACESEARCHER_H
