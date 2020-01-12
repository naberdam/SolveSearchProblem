//
// Created by amitai on 10/01/2020
//

#ifndef SOLIDPROJECT_EX2_FILECACHEMANAGER_H
#define SOLIDPROJECT_EX2_FILECACHEMANAGER_H

#include <vector>
#include <string>
#include <unordered_map>
#include <fstream>
#include <mutex>
#include <sstream>
#include "CacheManager.h"
#include <iostream>
#include <string.h>
#include <list>

#define CACHE_NAME_FILE "file"
using namespace std;

template<class Problem, class Solution>
class FileCacheManager : public CacheManager<Problem, Solution> {
public:
};


#endif //SOLIDPROJECT_EX2_FILECACHEMANAGER_H