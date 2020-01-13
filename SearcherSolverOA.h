//
// Created by nerya on 13/01/2020.
//

#ifndef UNTITLED2_SEARCHERSOLVEROA_H
#define UNTITLED2_SEARCHERSOLVEROA_H
#include "Solver.h"
#include "MyMatrixSearchable.h"
#include "MatrixBuilder.h"
#include "Searcher.h"
/*#include "AStarSearcher.h"*/
#include <vector>
#include <string>

using namespace std;

class SearcherSolver : public Solver<string, string> {
private:
    vector<vector<double >> detailsFromServerAboutMatrix;

public:

    virtual string solve(MyMatrixSearchable *problem) {
        /*MyMatrixSearchable matrixProblem = MatrixBuilder::createMatrix(problem);*/
        //todo: need to change it to vector of pair<int, int> instead of string as solution
        //todo: maybe changing the return value of matrixProblem to vector of states instead of string
        /*Searcher<string, pair<int, int>> *bestFS = new AStarSearcher<string, pair<int, int>>();
        string result = bestFS->search(&matrixProblem);
        delete bestFS;
        return result;*/
        return "";
    }

    void setDetailsFromServerAboutMatrix(const vector<vector<double>> &detailsFromServerAboutMatrix1) {
        SearcherSolver::detailsFromServerAboutMatrix = detailsFromServerAboutMatrix1;
    }
};


#endif //UNTITLED2_SEARCHERSOLVEROA_H
