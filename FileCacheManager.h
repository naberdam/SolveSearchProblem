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
    // for know which name to give for the files
    int numFiles = 0;
    // This map have keys that is the problem. The value will be the name of the file that give the solution
    unordered_map<string, string> mapOfCache;
public:
    // Bool methood that check if there is solution for this problem
    virtual bool isSavedSolution(Problem problem) {
        if (mapOfCache.count(problem) > 0) {
            return true;
        }
        return false;
    }
    // The methood will give to the user the solution
    virtual Solution getSolution(Problem problem) {
        if (isSavedSolution(problem)) {
            // Convert from const char* to string
            string nameFile = std::string(mapOfCache[problem]);
            string solution;
            // Open the stream and the file
            ifstream file;
            file.open(nameFile);
            getline(file, solution);
            // Return the solution in a string
            return solution;
        }
    }

    // The methhod will save the solution for this problem
    virtual void saveSolution(Problem problem, Solution solution) {
        // Give a name to the file.
        string nameOfFile = "FileSolution_" + std::to_string(numFiles);
        // Call for help methood
        insertObjectToFile(solution, nameOfFile);
        // Insert this solution to the map
        mapOfCache.insert({problem, nameOfFile});
    }
    // The distractor
    virtual ~FileCacheManager() {

    }
    // The help methhod  for insert the solution to the file
    void insertObjectToFile(string solution, string nameOfFileOfSolution) {
        cout<< endl<<endl<< numFiles;
        fstream file;
        // Open the stream and the file
        ofstream file1(nameOfFileOfSolution);
        file.open("FileSolution_" + std::to_string(numFiles), ios::out | ios::binary);
        // If there is a problem with the file
        if (!file) {
            throw "Error: problem with open the text file";
        }
        // Writing to the file and closing him
        file1 << solution;
        file1.close();
        // Increase the counter f the files for the next file to save.
        numFiles++;
    }
};


#endif //SOLIDPROJECT_EX2_FILECACHEMANAGER_H




