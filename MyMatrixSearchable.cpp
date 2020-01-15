//
// Created by amitai on 12/01/2020.
//

#include "MyMatrixSearchable.h"
#include <cmath>

int MyMatrixSearchable::xFatherOfCurrent(State<Point> &current) {
    int fatherX;
    //if current has father, so we want to keep his coordinates
    if (current.getFather() != NULL) {
        fatherX = current.getFather()->getState().getX();
    } else {
        //if there is not father, so we initialize xFatherOfCurrent and yFatherOfCurrent with (-1,-1)
        fatherX = -1;
    }
    return fatherX;
}

int MyMatrixSearchable::yFatherOfCurrent(State<Point> &current) {
    int fatherY;
    //if current has father, so we want to keep his coordinates
    if (current.getFather() != NULL) {
        fatherY = current.getFather()->getState().getY();
    } else {
        //if there is not father, so we initialize xFatherOfCurrent and yFatherOfCurrent with (-1,-1)
        fatherY = -1;
    }
    return fatherY;
}

State<Point> *MyMatrixSearchable::setNeighbourToVector(int x, int y, Direction direction, State<Point> &current) {
    Point *p1 = new Point(x, y);
    //add this neighbour with price up to date, direction and his father - current
    State<Point> *state1 = new State<Point>(p1, current.getCost() + matrixStatesByPoints[x][y]->getCost(),
                                            &current, direction);
    return state1;

}


vector<State<Point> *> MyMatrixSearchable::getPossibleNextStates(State<Point> &current) {
    vector<State<Point> *> result;
    int xCurrent = current.getState().getX();
    int yCurrent = current.getState().getY();
    //get coordinate of father
    int fatherX = xFatherOfCurrent(current), fatherY = yFatherOfCurrent(current);

    //if the index exist and the value isn't minus one, which is infinity, and if the index is not my father
    if (xCurrent < length - 1 && matrixStatesByPoints[xCurrent + 1][yCurrent]->getCost() >= 0 &&
        fatherX != xCurrent + 1) {
        result.push_back(setNeighbourToVector(xCurrent + 1, yCurrent, DOWN, current));
    }
    //if the index exist and the value isn't minus one, which is infinity, and if the index is not my father
    if (yCurrent < width - 1 && matrixStatesByPoints[xCurrent][yCurrent + 1]->getCost() >= 0 &&
        fatherY != yCurrent + 1) {
        result.push_back(setNeighbourToVector(xCurrent, yCurrent + 1, RIGHT, current));
    }
    //if the index exist and the value isn't minus one, which is infinity
    if (xCurrent > 0 && matrixStatesByPoints[xCurrent - 1][yCurrent]->getCost() >= 0 && fatherX != xCurrent - 1) {
        result.push_back(setNeighbourToVector(xCurrent - 1, yCurrent, UP, current));
    }
    //if the index exist and the value isn't minus one, which is infinity
    if (yCurrent > 0 && matrixStatesByPoints[xCurrent][yCurrent - 1]->getCost() >= 0 && fatherY != yCurrent - 1) {
        result.push_back(setNeighbourToVector(xCurrent, yCurrent - 1, LEFT, current));
    }
    return result;
}

State<Point> *
MyMatrixSearchable::setNeighbourToVectorWithManhattan(int x, int y, Direction direction, State<Point> &current,
                                                      State<Point> &goal, double manhattanDistanceCurrent) {
    //manhattan distance from neighbour of current to goal for the heuristic distance
    int manhattanDistance = abs(goal.getState().getX() - (x)) + abs(goal.getState().getY() - (y));
    manhattanDistance = abs(manhattanDistance - manhattanDistanceCurrent);
    Point *p1 = new Point(x, y);
    State<Point> *state1 = new State<Point>(p1,
                                            current.getCost() +
                                            matrixStatesByPoints[x][y]->getCost(), &current,
                                            direction);
    //set the heuristic distance with cost of current, cost of neighbour and the manhattanDistance
    state1->setHeuristicDistance(
            current.getCost() + matrixStatesByPoints[x][y]->getCost() + manhattanDistance);
    return state1;
}

vector<State<Point> *>
MyMatrixSearchable::getPossibleNextStatesWithManhattan(State<Point> &current, State<Point> &goal) {
    vector<State<Point> *> result;
    int xCurrent = current.getState().getX();
    int yCurrent = current.getState().getY();
    //get coordinates of father
    int fatherX = xFatherOfCurrent(current), fatherY = yFatherOfCurrent(current);

    //manhattan distance from current to goal for the heuristic distance
    double manhattanDistanceCurrent = abs(goal.getState().getX() - xCurrent) + abs(goal.getState().getY() - yCurrent);

    //if the index exist and the value isn't minus one, which is infinity, and if the index is not my father
    if (xCurrent < length - 1 && matrixStatesByPoints[xCurrent + 1][yCurrent]->getCost() >= 0 &&
        fatherX != xCurrent + 1) {
        result.push_back(setNeighbourToVectorWithManhattan(xCurrent + 1, yCurrent, DOWN, current, goal,
                                                           manhattanDistanceCurrent));
    }
    //if the index exist and the value isn't minus one, which is infinity, and if the index is not my father
    if (yCurrent < width - 1 && matrixStatesByPoints[xCurrent][yCurrent + 1]->getCost() >= 0 &&
        fatherY != yCurrent + 1) {
        result.push_back(setNeighbourToVectorWithManhattan(xCurrent, yCurrent + 1, RIGHT, current, goal,
                                                           manhattanDistanceCurrent));
    }
    //if the index exist and the value isn't minus one, which is infinity
    if (xCurrent > 0 && matrixStatesByPoints[xCurrent - 1][yCurrent]->getCost() >= 0 && fatherX != xCurrent - 1) {
        result.push_back(
                setNeighbourToVectorWithManhattan(xCurrent - 1, yCurrent, UP, current, goal, manhattanDistanceCurrent));
    }
    //if the index exist and the value isn't minus one, which is infinity
    if (yCurrent > 0 && matrixStatesByPoints[xCurrent][yCurrent - 1]->getCost() >= 0 && fatherY != yCurrent - 1) {
        result.push_back(setNeighbourToVectorWithManhattan(xCurrent, yCurrent - 1, LEFT, current, goal,
                                                           manhattanDistanceCurrent));
    }
    return result;


}

MyMatrixSearchable::~MyMatrixSearchable() {
    delete this->initializeStateByPoint;
    delete this->goalStateByPoint;
    unsigned int i, j;
    //delete all State<Point>*
    for (i = 0; i < this->matrixStatesByPoints.size(); ++i) {
        for (j = 0; j < this->matrixStatesByPoints[i].size(); ++j) {
            if (this->matrixStatesByPoints[i][j]) {
                delete this->matrixStatesByPoints[i][j];
            }
        }
    }
}






