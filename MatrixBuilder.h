//
// Created by amitai on 12/01/2020.
//

#ifndef UNTITLED2_MATRIXBUILDER_H
#define UNTITLED2_MATRIXBUILDER_H

#include "MyMatrixSearchable.h"
#include "State.h"
class MatrixBuilder {
 public:
  virtual ~MatrixBuilder();

  static MyMatrixSearchable *createMatrix(vector<vector<double>> detailsOnMatrix, string matrixToString);

};
#endif //UNTITLED2_MATRIXBUILDER_H
