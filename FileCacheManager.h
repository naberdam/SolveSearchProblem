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
#include <iostream>
#include <string.h>


#define CACHE_NAME_FILE "file"
using namespace std;

template<class Problem, class Solution>
class FileCacheManager : public CacheManager<Problem, Solution> {
private:
    int capacityOfCache;
    unordered_map<Problem, pair<Solution, list<string>::iterator>> mapOfCache;
    list<Problem> listOfKeys;
public:
    void insert(Problem prob, Solution sol) {
        //template<class Problem, class Solution>
        insertObjectToFile(prob, sol);
        auto checkObject = mapOfCache.find(prob);
        if (checkObject != mapOfCache.end()) {
            lru(checkObject);
            for (auto itr = listOfKeys.begin(); itr != listOfKeys.end(); itr++) {
                if ((*itr) == prob) {
                    listOfKeys.erase(itr);
                    break;
                }
            }
            mapOfCache[prob] = {sol, listOfKeys.begin()};

        } else if (mapOfCache.size() == (unsigned) capacityOfCache) {
            mapOfCache.erase(listOfKeys.back());
            listOfKeys.pop_back();
        }
        listOfKeys.push_front(prob);
        mapOfCache.insert({prob, {sol, listOfKeys.begin()}});
    }

    virtual ~FileCacheManager() {

    }

    void lru(typename unordered_map<Problem, pair<Solution, list<string>::iterator>>::iterator &it) {
        listOfKeys.erase(it->second.second);
        listOfKeys.push_front(it->first);
        it->second.second = listOfKeys.begin();
    }

    template<class Func>
    void foreach(Func f) {
        for (auto it = listOfKeys.begin(); it != listOfKeys.end(); ++it) {
            f(mapOfCache.find(*it)->second.first);

        }
    }

    Solution checkItemInFile(string key) {
        Solution objectFromCacheOrFile;
        fstream inputTxt;
        inputTxt.open(Solution::class_name + key, ios::in | ios::binary);
        if (!inputTxt) {
            throw "Error: problem with open the text file";
        }
        if (inputTxt.read((char *) &objectFromCacheOrFile, sizeof(objectFromCacheOrFile))) {
            inputTxt.close();
            insert(key, objectFromCacheOrFile);
            auto item = mapOfCache.find(key);
            lru(item);
            return objectFromCacheOrFile;
        } else {
            throw "Error:problem in reading data from text file";
        }
    }

    void insertObjectToFile(Problem key, Solution newObject) {
        fstream file;
        file.open(Solution::class_name + key, ios::out | ios::binary);
        if (!file) {
            throw "Error: problem with open the text file";
        }
        file.write((char *) &newObject, sizeof(newObject));
        file.close();
    }

/*
    virtual ~CacheManager() {}
*/



};


#endif //SOLIDPROJECT_EX2_FILECACHEMANAGER_H




