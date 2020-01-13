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

class SearcherSolver : public Solver<MyMatrixSearchable*, string> {
public:

    virtual string solve(MyMatrixSearchable *problem) {
        /*MyMatrixSearchable matrixProblem = MatrixBuilder::createMatrix(problem);*/
        //todo: need to change it to vector of pair<int, int> instead of string as solution
        //todo: maybe changing the return value of matrixProblem to vector of states instead of string
        /*Searcher<string, pair<int, int>> *bestFS = new AStarSearcher<string, pair<int, int>>();
        string result = bestFS->search(&matrixProblem);
        delete bestFS;
        return result;*/
        cout << "succeed to enter SearcherSolver" << endl;
        cout << "blb" << endl;
        return "";
    }
};


#endif //UNTITLED2_SEARCHERSOLVEROA_H
