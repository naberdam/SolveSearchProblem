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

// Cache manager for generic option. so when we want another implemention with no just file cache.
// we will use problem and solution
template<class Problem, class Solution>
class CacheManager {
public:
    // Bool methood that check if there is solution for this problem
    virtual bool isSavedSolution(Problem problem) = 0;

    // The methood will give to the user the solution
    virtual Solution getSolution(Problem problem) = 0;

    // The methhod will save the solution for this problem
    virtual void saveSolution(Problem problem, Solution solution) = 0;

    // The distractor
    virtual ~CacheManager() {

    }

};


#endif //SOLIDPROJECT_EX2_CACHEMANAGER_H
