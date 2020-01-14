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

template<typename Problem, typename Solution>
class FileCacheManager : public CacheManager<Problem, Solution> {
private:
    int numFiles = 0;
    unordered_map<string, string> mapOfCache;
public:
    virtual bool isSavedSolution(Problem problem) {
        if (mapOfCache.count(problem) > 0) {
            return true;
        }
        return false;
    }

    virtual Solution getSolution(Problem problem) {
        if (isSavedSolution(problem)) {
            string nameFile = std::string(mapOfCache[problem]);
            string solution;
            ifstream file;
            file.open(nameFile);
            getline(file, solution);
            return solution;
        }
    }


    virtual void saveSolution(Problem problem, Solution solution) {
        string nameOfFile = "FileSolution_" + std::to_string(numFiles);
        insertObjectToFile(solution, nameOfFile);
        mapOfCache.insert({problem, nameOfFile});
    }
    virtual ~FileCacheManager() {

    }

    void insertObjectToFile(string solution, string nameOfFileOfSolution) {
        fstream file;
        ofstream file1(nameOfFileOfSolution);
        file.open("FileSolution_" + std::to_string(numFiles), ios::out | ios::binary);
        if (!file) {
            throw "Error: problem with open the text file";
        }
        file1 << solution;
        file1.close();
        numFiles++;
    }
};


#endif //SOLIDPROJECT_EX2_FILECACHEMANAGER_H




