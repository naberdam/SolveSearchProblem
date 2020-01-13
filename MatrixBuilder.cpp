//
// Created by amitai on 12/01/2020.
//


#include "MatrixBuilder.h"
#include "Point.h"

MyMatrixSearchable *MatrixBuilder::createMatrix(vector<vector<double> > detailsOnMatrix, string matrixToString) {
    vector<double> detailsGoalPoint = detailsOnMatrix.back();
    detailsOnMatrix.pop_back();
    Point* goal = new Point((int) detailsGoalPoint[0], (int) detailsGoalPoint[1]);
    vector<double> detailsStartPoint = detailsOnMatrix.back();
    detailsOnMatrix.pop_back();
    Point* start = new Point((int) detailsStartPoint[0],  (int) detailsStartPoint[1]);
    State<Point>* goalState = new State<Point>(goal, detailsOnMatrix[goal->getX()][goal->getY()], nullptr, NOT);
    State<Point>* startState = new State<Point>(start, detailsOnMatrix[start->getX()][start->getY()], nullptr, NOT);
    MyMatrixSearchable* myMatrixSearchable = new MyMatrixSearchable(detailsOnMatrix, startState, goalState, matrixToString);
    return myMatrixSearchable;
}
