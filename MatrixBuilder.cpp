//
// Created by amitai on 12/01/2020.
//


#include <limits>
#include "MatrixBuilder.h"
#include "Point.h"

MyMatrixSearchable *MatrixBuilder::createMatrix(vector<vector<double> > detailsOnMatrix, string matrixToString) {
  //take the line of the coordinates of goalState
  vector<double> detailsGoalPoint = detailsOnMatrix.back();
  //delete (x,y) of goalState from the matrix
  detailsOnMatrix.pop_back();
  Point *goal = new Point((int) detailsGoalPoint[0], (int) detailsGoalPoint[1]);
  //take the line of the coordinates of initializeState
  vector<double> detailsStartPoint = detailsOnMatrix.back();
  //delete (x,y) of initializeState from the matrix
  detailsOnMatrix.pop_back();
  Point *start = new Point((int) detailsStartPoint[0], (int) detailsStartPoint[1]);
  //now detailsOnMatrix only contains the matrix itself without the coordinates of goalState and initializeState


  State<Point> *goalState = new State<Point>(goal, detailsOnMatrix[goal->getX()][goal->getY()], nullptr, NOT);
  State<Point> *startState = new State<Point>(start, detailsOnMatrix[start->getX()][start->getY()], nullptr, NOT);

  //this vector will be the real matrix we will use in MyMatrixSearchable
  vector<vector<State<Point> *>> matrixStatesByPoints;
  unsigned int i;
  unsigned int j;
  for (i = 0; i < detailsOnMatrix.size(); ++i) {
    vector<State<Point> *> lineInDetailsOnMatrix;
    for (j = 0; j < detailsOnMatrix[i].size(); ++j) {
      Point *p = new Point(i, j);
      lineInDetailsOnMatrix.push_back(new State<Point>(p, detailsOnMatrix[i][j], nullptr, NOT));
      //initialize the heuristic distance to be infinity for the algorithms that will use ComparatorByHeuristic
      lineInDetailsOnMatrix[lineInDetailsOnMatrix.size() - 1]->setHeuristicDistance(numeric_limits<double>::infinity());
    }
    matrixStatesByPoints.push_back(lineInDetailsOnMatrix);
  }

  //create the matrix we will use during the algorithms
  MyMatrixSearchable *myMatrixSearchable = new MyMatrixSearchable(matrixStatesByPoints, startState, goalState,
                                                                  matrixToString);
  return myMatrixSearchable;
}

MatrixBuilder::~MatrixBuilder() {}
