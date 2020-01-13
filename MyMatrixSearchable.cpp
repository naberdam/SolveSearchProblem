//
// Created by amitai on 12/01/2020.
//

#include "MyMatrixSearchable.h"
#include <cmath>

vector<State<Point>*> MyMatrixSearchable::getPossibleNextStates(State<Point> &current) {

    vector<State<Point>*> result;
    int xCurrent = current.getState().getX();
    int yCurrent = current.getState().getY();
    int fatherX, fatherY;
    if (current.getFather() != NULL) {
        fatherX = current.getFather()->getState().getX();
        fatherY = current.getFather()->getState().getY();
    }
    else {
        fatherX = fatherY = -1;
    }
    //if the index exist and the value isn't minus one, which is infinity
    if (xCurrent < width - 1 && matrixStatesByPoints[xCurrent + 1][yCurrent] >= 0 && fatherX != xCurrent + 1) {
        result.push_back(new State<Point>(std::make_pair(xCurrent + 1, yCurrent), current.getCost() + matrixStatesByPoints[xCurrent + 1][yCurrent], &current, DOWN));
    }
    if (yCurrent < length - 1 && matrixStatesByPoints[xCurrent][yCurrent + 1] >= 0 && fatherY != yCurrent + 1) {
        result.push_back(new State<Point>(std::make_pair(xCurrent, yCurrent + 1), current.getCost() + matrixStates[xCurrent][yCurrent + 1], &current, RIGHT));
    }
    if (xCurrent > 0 && matrixStates[xCurrent - 1][yCurrent] >= 0 && fatherX != xCurrent - 1) {
        result.push_back(new State<Point>(std::make_pair(xCurrent - 1, yCurrent), current.getCost() + matrixStates[xCurrent - 1][yCurrent], &current, UP));
    }
    if (yCurrent > 0 && matrixStates[xCurrent][yCurrent - 1] >= 0 && fatherY != yCurrent - 1) {
        result.push_back(new State<Point>(std::make_pair(xCurrent, yCurrent - 1), current.getCost() + matrixStates[xCurrent][yCurrent - 1], &current, LEFT));
    }
    return result;
}




