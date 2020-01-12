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
template <typename Problem, typename Solution>
class FileCacheManager : public CacheManager<Problem, Solution> {
private:
    int capacityOfCache;
    unordered_map<string, pair<const char*, list<string>::iterator>> mapOfCache;
    list<string> listOfKeys;
public:
    void insert(string prob, const char* sol) {
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

    void lru(typename unordered_map<string, pair<const char*, list<string>::iterator>>::iterator &it) {
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

    const char* checkItemInFile(string key) {
        const char* objectFromCacheOrFile;
        fstream inputTxt;
        inputTxt.open(key, ios::in | ios::binary);
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

    void insertObjectToFile(string key, const char* newObject) {
        fstream file;
        file.open(key, ios::out | ios::binary);
        if (!file) {
            throw "Error: problem with open the text file";
        }
        file.write((char *) &newObject, sizeof(newObject));
        file.close();
    }
};


#endif //SOLIDPROJECT_EX2_FILECACHEMANAGER_H




