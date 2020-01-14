//
// Created by nerya on 13/01/2020.
//

#ifndef UNTITLED2_SEARCHERSOLVEROA_H
#define UNTITLED2_SEARCHERSOLVEROA_H

#include "Solver.h"
#include "MyMatrixSearchable.h"
#include "MatrixBuilder.h"
#include "Searcher.h"
#include "AStar.h"
#include "BestFirstSearch.h"
#include "BFS.h"
#include "DFS.h"
#include <vector>
#include <string>

using namespace std;

template<typename T>
class SearcherSolver : public Solver<Searchable<T> *, string> {
public:

    virtual string solve(Searchable<T> *problem) {
        Searcher<string, T> *bestFS = new DFS<T>();
        string result = bestFS->search(problem);
        cout << bestFS->getNumberOfNodesEvaluated() << endl;
        delete bestFS;
        return result;
    }

    virtual ~SearcherSolver();
};


#endif //UNTITLED2_SEARCHERSOLVEROA_H

template<typename T>
SearcherSolver<T>::~SearcherSolver() {

}
