//
// Created by amitai on 12/01/2020.
//

#ifndef UNTITLED2_MYMATRIXSEARCHABLE_H
#define UNTITLED2_MYMATRIXSEARCHABLE_H

#include <string>
#include "Searchable.h"
#include "Point.h"


class MyMatrixSearchable : public Searchable<Point> {
    unsigned long length;
    unsigned long width;
    State<Point> *initStateByPoint;
    State<Point> *goalStateByPoint;
    vector<vector<State<Point>*>> matrixStatesByPoints;
    string representationMatrixInString;

public:

    MyMatrixSearchable(vector<vector<State<Point>*>> &matrix, State<Point> *&initState,
                       State<Point> *&goalState, const string matrixInString) : matrixStatesByPoints(matrix),
                                                                                initStateByPoint(initState),
                                                                                goalStateByPoint(goalState),
                                                                                representationMatrixInString(
                                                                                        matrixInString) {
        width = matrixStatesByPoints[0].size();
        length = matrixStatesByPoints.size();
    }

    virtual State<Point> *getInitializeState() {
        return initStateByPoint;
    }

    virtual State<Point> *getGoalState() {
        return goalStateByPoint;
    }

    virtual vector<State<Point> *> getPossibleNextStates(State<Point> &current);

    friend ostream &operator<<(ostream &out, const MyMatrixSearchable *&c) {
        out << c->representationMatrixInString;
        return out;
    }
};



#endif //UNTITLED2_MYMATRIXSEARCHABLE_H
