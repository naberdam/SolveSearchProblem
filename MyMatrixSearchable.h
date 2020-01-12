//
// Created by amitai on 12/01/2020.
//

#ifndef UNTITLED2_MYMATRIXSEARCHABLE_H
#define UNTITLED2_MYMATRIXSEARCHABLE_H
#include <string>
#include "Searchable.h"
using namespace std;

class MyMatrixSearchable: public Searchable<pair<int, int>> {

    vector<vector<int>> matrixStates;
    unsigned long length;
    unsigned long width;
    State<pair<int, int>> initState;
    State<pair<int, int>> goalState;

public:

    MyMatrixSearchable(const vector<vector<int>> &matrix, State<pair<int, int>> &initState,
                       State<pair<int, int>> &goalState) :matrixStates(matrix), initState(initState), goalState(goalState) {
        width = matrixStates[0].size();
        length = matrixStates.size();
    }

    virtual State<pair<int, int>> *getInitialState() {
        return &initState;
    }

    virtual State<pair<int, int>> *getGoalState() {
        return &goalState;
    }

    virtual vector<State<pair<int, int>>*> getPossibleNextStates(State<pair<int, int>> &current);


};
#endif //UNTITLED2_MYMATRIXSEARCHABLE_H
