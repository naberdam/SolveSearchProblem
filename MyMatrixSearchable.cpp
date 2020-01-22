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
  //if the index exist and the value isn't minus one, which is infinity
  if (xCurrent > 0 && matrixStatesByPoints[xCurrent - 1][yCurrent]->getCost() >= 0 && fatherX != xCurrent - 1) {
    result.push_back(setNeighbourToVector(xCurrent - 1, yCurrent, UP, current));
  }
  //if the index exist and the value isn't minus one, which is infinity, and if the index is not my father
  if (yCurrent < width - 1 && matrixStatesByPoints[xCurrent][yCurrent + 1]->getCost() >= 0 &&
      fatherY != yCurrent + 1) {
    result.push_back(setNeighbourToVector(xCurrent, yCurrent + 1, RIGHT, current));
  }
  //if the index exist and the value isn't minus one, which is infinity
  if (yCurrent > 0 && matrixStatesByPoints[xCurrent][yCurrent - 1]->getCost() >= 0 && fatherY != yCurrent - 1) {
    result.push_back(setNeighbourToVector(xCurrent, yCurrent - 1, LEFT, current));
  }
  return result;
}

double MyMatrixSearchable::setHeuristicForNode(State<Point> &nodeToChange, State<Point> &goal) {
  int manhattanDistance = abs(goal.getState().getX() - (nodeToChange.getState().getX()))
      + abs(goal.getState().getY() - (nodeToChange.getState().getY()));
  return manhattanDistance;
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






