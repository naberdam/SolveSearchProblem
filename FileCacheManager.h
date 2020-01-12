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



/*//
// Created by nerya on 27/11/2019.
//

#ifndef EX2_EX2_H
#define EX2_EX2_H

#include <iostream>
#include <string.h>
#include <string>
#include <list>
#include <unordered_map>
#include <fstream>

using namespace std;
//the basic of this algorithm is from youtube - https://www.youtube.com/watch?v=8-FZRAjR7qU

template<class T>
class CacheManager {
private:
    int capacityOfCache;
    unordered_map<string, pair<T, list<string>::iterator>> mapOfCache;
    list<string> listOfKeys;

public:
    CacheManager<T>(int capacityOfCache1) : capacityOfCache(capacityOfCache1) {}

    T get(string key) {
        auto item = mapOfCache.find(key);
        if (item != mapOfCache.end()) {
            lru(item);
            return item->second.first;
        } else {
            return checkItemInFile(key);
        }

    }

    void insert(string key, T newObject) {
        insertObjectToFile(key, newObject);
        auto checkObject = mapOfCache.find(key);
        if (checkObject != mapOfCache.end()) {
            lru(checkObject);
            for (auto itr = listOfKeys.begin(); itr != listOfKeys.end(); itr++) {
                if ((*itr) == key) {
                    listOfKeys.erase(itr);
                    break;
                }
            }
            mapOfCache[key] = {newObject, listOfKeys.begin()};

        } else if (mapOfCache.size() == (unsigned) capacityOfCache) {
            mapOfCache.erase(listOfKeys.back());
            listOfKeys.pop_back();
        }
        listOfKeys.push_front(key);
        mapOfCache.insert({key, {newObject, listOfKeys.begin()}});
    }

    void lru(typename unordered_map<string, pair<T, list<string>::iterator>>::iterator &it) {
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

    T checkItemInFile(string key) {
        T objectFromCacheOrFile;
        fstream inputTxt;
        inputTxt.open(T::class_name + key, ios::in | ios::binary);
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

    void insertObjectToFile(string key, T newObject) {
        fstream file;
        file.open(T::class_name + key, ios::out | ios::binary);
        if (!file) {
            throw "Error: problem with open the text file";
        }
        file.write((char *) &newObject, sizeof(newObject));
        file.close();
    }

    virtual ~CacheManager() {}
};


#endif //EX2_EX2_H*/
