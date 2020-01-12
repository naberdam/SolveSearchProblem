//
// Created by amitai on 12/01/2020.
//

#include "MyMatrixSearchable.h"
#include <cmath>

vector<State<pair<int, int>>*> MyMatrixSearchable::getPossibleNextStates(State<pair<int, int>> &current) {
    vector<State<pair<int, int>>*> result;
    int i = current.getState().first;
    int j = current.getState().second;
    int fatherI, fatherJ;
    if (current.getFather() != NULL) {
        fatherI = current.getFather()->getState().first;
        fatherJ = current.getFather()->getState().second;
    }
    else {
        fatherI = fatherJ = -1;
    }
    //if the index exist and the value isn't minus one, which is infinity
    if (i < width-1 && matrixStates[i+1][j] >= 0 && fatherI != i+1) {
        result.push_back(new State<pair<int,int>>(std::make_pair(i + 1, j), current.getCost() + matrixStates[i+1][j], &current, DOWN));
    }
    if (j < length-1 && matrixStates[i][j+1] >= 0 && fatherJ != j+1) {
        result.push_back(new State<pair<int,int>>(std::make_pair(i, j + 1), current.getCost() + matrixStates[i][j+1], &current, RIGHT));
    }
    if (i > 0 && matrixStates[i-1][j] >= 0 && fatherI != i-1) {
        result.push_back(new State<pair<int,int>>(std::make_pair(i - 1, j), current.getCost() + matrixStates[i-1][j], &current, UP));
    }
    if (j > 0 && matrixStates[i][j-1] >= 0 && fatherJ != j-1) {
        result.push_back(new State<pair<int,int>>(std::make_pair(i, j - 1), current.getCost() + matrixStates[i][j-1], &current, LEFT));
    }
    return result;
}

