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
#include "BestFirstSearch.h"
#include "BFS.h"
#include <vector>
#include <string>

using namespace std;
template <typename T>
class SearcherSolver : public Solver<Searchable<T>*, string> {
public:

    virtual string solve(Searchable<T> *problem) {
        Searcher<string, T> *bestFS = new BFS<T>();
        cout << "succeed to enter SearcherSolver" << endl;
        string result = bestFS->search(problem);
        cout << "succeed to enter SearcherSolver2" << endl;
        cout << bestFS->getNumberOfNodesEvaluated() << endl;
        delete bestFS;
        cout << result << endl;
        return result;
    }
};


#endif //UNTITLED2_SEARCHERSOLVEROA_H
