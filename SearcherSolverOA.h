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
    Searcher<string, T> *bestFS = new BestFirstSearch<T>();
    //get solution of problem
    string result = bestFS->search(problem);
    cout << "how much kodkodim BestFS: " << bestFS->getNumberOfNodesEvaluated() << endl;
    delete bestFS;

    Searcher<string, T> *bestFS1 = new AStar<T>();
    //get solution of problem
    string result1 = bestFS1->search(problem);
    cout << "how much kodkodim AStar: " << bestFS1->getNumberOfNodesEvaluated() << endl;
    delete bestFS1;

    Searcher<string, T> *bestFS2 = new BFS<T>();
    //get solution of problem
    string result2 = bestFS2->search(problem);
    cout << "how much kodkodim BFS: " << bestFS2->getNumberOfNodesEvaluated() << endl;
    delete bestFS2;

    Searcher<string, T> *bestFS3 = new DFS<T>();
    //get solution of problem
    string result3 = bestFS3->search(problem);
    cout << "how much kodkodim DFS: " << bestFS3->getNumberOfNodesEvaluated() << endl;
    delete bestFS3;
    return result;
  }

  virtual ~SearcherSolver() {}
};

#endif //UNTITLED2_SEARCHERSOLVEROA_H
