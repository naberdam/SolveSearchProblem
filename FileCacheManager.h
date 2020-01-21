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
#include <functional>


#define CACHE_NAME_FILE "file"
using namespace std;

template<typename Problem, typename Solution>
class FileCacheManager : public CacheManager<Problem, Solution> {
public:
    // The constructor
    FileCacheManager() {}

    // Bool methood that check if there is solution for this problem
    virtual bool isSavedSolution(Problem problem) {
        // Use a function hash for the name of the file
        hash<string> hasher;
        std::size_t hash = hasher(problem);
        string nameFile = to_string(hash);
        // Open the stream and the file
        ifstream file;
        file.open(nameFile);
        // check if the file exist
        if (file) {
            return true;
        }
        return false;
    }

    // The methood will give to the user the solution
    virtual Solution getSolution(Problem problem) {
        if (isSavedSolution(problem)) {
            hash<string> hasher;
            // Get the hash of the problem
            std::size_t hash = hasher(problem);
            string nameFile = to_string(hash);
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
        hash<string> hasher;
        size_t hash = hasher(problem);
        string nameFile = to_string(hash);        // Call for help methood
        insertObjectToFile(solution, nameFile);
    }

    // The distractor
    virtual ~FileCacheManager() {

    }

    // The help methhod  for insert the solution to the file
    void insertObjectToFile(string solution, string nameOfFileOfSolution) {
        // Open the stream and the file
        fstream file(nameOfFileOfSolution);
        file.open(nameOfFileOfSolution, ios::out | ios::binary);
        // If there is a problem with the file
        if (!file) {
            throw "Error: problem with open the text file";
        }
        // Writing to the file and closing him
        file << solution;
        file.close();
    }
};


#endif //SOLIDPROJECT_EX2_FILECACHEMANAGER_H




