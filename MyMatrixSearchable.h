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
  vector<vector<State<Point> *>> matrixStatesByPoints;
  State<Point> *initializeStateByPoint;
  State<Point> *goalStateByPoint;
  string representationMatrixInString;
  long long length;
  long long width;

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

  virtual vector<State<Point> *> getPossibleNextStates(State<Point> &current);

  virtual State<Point> *setNeighbourToVector(int x, int y, Direction direction, State<Point> &current);

  friend ostream &operator<<(ostream &out, const MyMatrixSearchable *&c) {
    out << c->representationMatrixInString;
    return out;
  }

  virtual double setHeuristicForNode(State<Point> &nodeToChange, State<Point> &goal);
};

#endif //UNTITLED2_MYMATRIXSEARCHABLE_H
