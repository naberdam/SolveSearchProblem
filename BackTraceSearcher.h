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
    //how much nodes did i use to go the goalState
    unsigned long evaluatedNodes;

    string setCostInResult(State<T>* item) {
        string result;
        result += to_string(item->getCost());
        result += ")";
        return result;
    }

    string firstAddingToResultOrNot(bool &firstTimeAddingToResult) {
        if (firstTimeAddingToResult) {
            firstTimeAddingToResult = false;
            return "";
        }
        return ", ";
    }

protected:

    //return back trace of our path
    string backTrace(State<T> *current, Searchable<T> *searchable) {
        stack<State<T> *> trace;
        State<T> *tempState = current;
        string result = "";

        //make trace that in the top it will has the initializeState and in the end it will has the goalState
        //and all this for the string we want to send with which direction we did each time
        while (!(*tempState == *searchable->getInitializeState())) {
            trace.push(tempState);
            tempState = tempState->getFather();
        }
        //push the initializeState because it did not enter int the while loop
        trace.push(searchable->getInitializeState());
        bool firstTimeAddingToResult = true;

        while (!trace.empty()) {
            State<T>* item = trace.top();
            switch (item->getDirection()) {
                case UP:
                    result += firstAddingToResultOrNot(firstTimeAddingToResult);
                    result += "Up (";
                    result += this->setCostInResult(item);
                    break;
                case DOWN:
                    result += firstAddingToResultOrNot(firstTimeAddingToResult);
                    result += "Down (";
                    result += this->setCostInResult(item);
                    break;
                case LEFT:
                    result += firstAddingToResultOrNot(firstTimeAddingToResult);
                    result += "Left (";
                    result += this->setCostInResult(item);
                    break;
                case RIGHT:
                    result += firstAddingToResultOrNot(firstTimeAddingToResult);
                    result += "Right (";
                    result += this->setCostInResult(item);
                    break;
                default:
                    break;
            }
            trace.pop();
        }
        return result;
    }

    virtual string noPathFromInitializeToGoal(Searchable<T> *searchable) {
        string msgToServerWithNoPath;
        msgToServerWithNoPath += "there is not trace from (";
        msgToServerWithNoPath += to_string(searchable->getInitializeState()->getState().getX());
        msgToServerWithNoPath += ",'";
        msgToServerWithNoPath += to_string(searchable->getInitializeState()->getState().getY());
        msgToServerWithNoPath += ") to (";
        msgToServerWithNoPath += to_string(searchable->getGoalState()->getState().getX());
        msgToServerWithNoPath += ",'";
        msgToServerWithNoPath += to_string(searchable->getGoalState()->getState().getY());
        msgToServerWithNoPath += ")";
        return msgToServerWithNoPath;
    }

    virtual void increaseNumberOfNodesEvaluated() {
        ++evaluatedNodes;
    }

    virtual State<T> *popOpenList() = 0;
    virtual unsigned long getOpenListSize() = 0;
    virtual void addToOpenList(State<T> *current) = 0;
    virtual void addToCloseList(State<T> *current) = 0;
    virtual bool doWeHaveThisNodeInOpenList(State<T> *current) = 0;
    virtual bool doWeHaveThisNodeInClosedList(State<T> *current) = 0;
    virtual void deleteEverything() = 0;

public:
    BackTraceSearcher() : evaluatedNodes(0) {}

    virtual Solution search(Searchable<T> *searchable) = 0;

    virtual unsigned long getNumberOfNodesEvaluated() {
        return evaluatedNodes;
    }

    virtual ~BackTraceSearcher() {}


};

#endif //UNTITLED2_BACKTRACESEARCHER_H
