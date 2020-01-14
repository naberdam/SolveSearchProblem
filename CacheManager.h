//
// Created by amitai on 10/01/2020
//

#ifndef SOLIDPROJECT_EX2_CACHEMANAGER_H
#define SOLIDPROJECT_EX2_CACHEMANAGER_H

#include <string>
#include <bits/unordered_map.h>
#include <map>
#include <fstream>
#include <iostream>
using namespace std;

template <class Problem ,class Solution>
class CacheManager {
protected:
    map<Problem, Solution> solutions;

public:
    virtual bool isSavedSolution(Problem problem) = 0;

    virtual Solution getSolution(Problem problem)= 0;

    virtual void saveSolution(Problem problem, Solution solution)=0 ;
};

/*template<class Problem, class Solution>
bool CacheManager<Problem, Solution>::isSavedSolution(Problem problem) {
    return solutions.count(problem) != 0;
}

template<class Problem, class Solution>
Solution CacheManager<Problem, Solution>::getSolution(Problem problem) {
    return solutions[problem];
}

template<class Problem, class Solution>
void CacheManager<Problem, Solution>::saveSolution(Problem problem, Solution solution) {
    solutions[problem] = solution;
}*/
#endif //SOLIDPROJECT_EX2_CACHEMANAGER_H
