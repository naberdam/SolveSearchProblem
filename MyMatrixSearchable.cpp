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
    if (xCurrent < width - 1 && matrixStatesByPoints[xCurrent + 1][yCurrent]->getCost() >= 0 && fatherX != xCurrent + 1) {
        Point *p1 = new Point(xCurrent + 1, yCurrent);
        result.push_back(new State<Point>(p1, current.getCost() + matrixStatesByPoints[xCurrent + 1][yCurrent]->getCost(), &current, DOWN));
    }
    if (yCurrent < length - 1 && matrixStatesByPoints[xCurrent][yCurrent + 1]->getCost() >= 0 && fatherY != yCurrent + 1) {
        Point *p2 = new Point(xCurrent, yCurrent + 1);
        result.push_back(new State<Point>(p2, current.getCost() + matrixStatesByPoints[xCurrent][yCurrent + 1]->getCost(), &current, RIGHT));
    }
    if (xCurrent > 0 && matrixStatesByPoints[xCurrent - 1][yCurrent]->getCost() >= 0 && fatherX != xCurrent - 1) {
        Point *p3 = new Point(xCurrent - 1, yCurrent);
        result.push_back(new State<Point>(p3, current.getCost() + matrixStatesByPoints[xCurrent - 1][yCurrent]->getCost(), &current, UP));
    }
    if (yCurrent > 0 && matrixStatesByPoints[xCurrent][yCurrent - 1]->getCost() >= 0 && fatherY != yCurrent - 1) {
        Point *p4 = new Point(xCurrent, yCurrent - 1);
        result.push_back(new State<Point>(p4, current.getCost() + matrixStatesByPoints[xCurrent][yCurrent - 1]->getCost(), &current, LEFT));
    }
    return result;
}




