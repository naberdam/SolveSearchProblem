//
// Created by amitai on 12/01/2020.
//

#ifndef UNTITLED2_MYMATRIXSEARCHABLE_H
#define UNTITLED2_MYMATRIXSEARCHABLE_H

#include <string>
#include <utility>
#include "Searchable.h"
#include "Point.h"


class MyMatrixSearchable : public Searchable<Point> {
    unsigned long length;
    unsigned long width;
    State<Point> *initializeStateByPoint;
    State<Point> *goalStateByPoint;
    vector<vector<State<Point> *>> matrixStatesByPoints;
    string representationMatrixInString;

public:

    MyMatrixSearchable(vector<vector<State<Point> *>> &matrix, State<Point> *&initState,
                       State<Point> *&goalState, string &matrixInString) : matrixStatesByPoints(matrix),
                                                                           initializeStateByPoint(initState),
                                                                           goalStateByPoint(goalState),
                                                                           representationMatrixInString(std::move(
                                                                                   matrixInString)) {
        width = matrixStatesByPoints[0].size();
        length = matrixStatesByPoints.size();
    }

    virtual int xFatherOfCurrent(State<Point> &current);

    virtual int yFatherOfCurrent(State<Point> &current);

    virtual ~MyMatrixSearchable();

    virtual State<Point> *getInitializeState() {
        return initializeStateByPoint;
    }

    virtual State<Point> *getGoalState() {
        return goalStateByPoint;
    }

    virtual vector<State<Point> *> getPossibleNextStatesWithManhattan(State<Point> &current, State<Point> &goal);

    virtual vector<State<Point> *> getPossibleNextStates(State<Point> &current);

    virtual State<Point> *setNeighbourToVector(int x, int y, Direction direction, State<Point> &current);

    virtual State<Point> *setNeighbourToVectorWithManhattan(int x, int y, Direction direction, State<Point> &current,
                                                            State<Point> &goal, double manhattanDistanceCurrent);

    friend ostream &operator<<(ostream &out, const MyMatrixSearchable *&c) {
        out << c->representationMatrixInString;
        return out;
    }
};


#endif //UNTITLED2_MYMATRIXSEARCHABLE_H
