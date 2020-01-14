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

    virtual ~CacheManager();
};

template<class Problem, class Solution>
CacheManager<Problem, Solution>::~CacheManager() {

}

#endif //SOLIDPROJECT_EX2_CACHEMANAGER_H
