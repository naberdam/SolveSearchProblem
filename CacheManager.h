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
#define CACHE_FILE_NAME "data.txt"

using namespace std;

template <class Problem ,class Solution>
class CacheManager {
protected:
    map<Problem, Solution> solutions;

public:
    virtual bool isSavedSolution(Problem problem);

    virtual Solution getSolution(Problem problem);

    virtual void saveSolution(Problem problem, Solution solution);
};

template<class Problem, class Solution>
bool CacheManager<Problem, Solution>::isSavedSolution(Problem problem) {
    /*cout<<"isSavedSolution"<<endl;*/
    return solutions.count(problem) != 0;
}

template<class Problem, class Solution>
Solution CacheManager<Problem, Solution>::getSolution(Problem problem) {
    /*cout<<"getSolution"<<endl;*/
    return solutions[problem];
}

template<class Problem, class Solution>
void CacheManager<Problem, Solution>::saveSolution(Problem problem, Solution solution) {
    /*cout<<"saveSolution"<<endl;*/
    solutions[problem] = solution;
}
#endif //SOLIDPROJECT_EX2_CACHEMANAGER_H
