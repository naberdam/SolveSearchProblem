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


template <class Problem ,class Solution>
class FileCacheManager: public CacheManager<Problem,Solution> {
public:
    FileCacheManager();

    ~FileCacheManager();

    void load();

    void save();
};

template<class Problem, class Solution>
void FileCacheManager<Problem, Solution>::load() {
    string line;
    ifstream file;
    file.open(CACHE_FILE_NAME, ios::in);

    if (file.is_open()) {
        while (getline(file, line)) {
            int i = 0;
            string question, answer;

            // question until @
            while (line[i] != '@') {
                question += line[i];
                ++i;
            }
            ++i;

            // answer until end
            while (i < line.length()) {
                answer += line[i];
                ++i;
            }

            this->solutions.insert(pair<string,string>(question,answer));
        }
        file.close();
    }
}

template<class Problem, class Solution>
void FileCacheManager<Problem, Solution>::save() {
    ofstream file(CACHE_FILE_NAME);

    if (file.is_open()) {
        for (auto &qa : this->solutions) {
            file << qa.first << "@" << qa.second << endl;
        }
        file.close();
    } else {
        throw "unable to open file";
    }
}

template<class Problem, class Solution>
FileCacheManager<Problem, Solution>::FileCacheManager() {
    this->load();
}

template<class Problem, class Solution>
FileCacheManager<Problem, Solution>::~FileCacheManager() {
    this->save();
}
#endif //SOLIDPROJECT_EX2_FILECACHEMANAGER_H