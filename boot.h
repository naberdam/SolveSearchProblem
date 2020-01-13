//
// Created by nerya on 10/01/2020.
//

#ifndef UNTITELD2_BOOT_H
#define UNTITELD2_BOOT_H

#include "FileCacheManager.h"
#include "MyTestClientHandler.h"
#include "MyClientHandler.h"
#include "MySerialServer.h"
#include "StringReverser.h"
#include "Point.h"
#include "Searchable.h"
#include "SearcherSolverOA.h"
using namespace std;

namespace boot {
    template <class Problem, class Solution>
    class Main {
    public:
        Main() {}
        int main1(int argc, char** argv) {
            auto cm = new FileCacheManager<Problem, Solution>();
            /*auto solver = new StringReverser<string, string>();
            auto *c = new MyTestClientHandler<string, string>(cm, solver);*/
            auto solver = new SearcherSolver<Point>();
            auto *c = new MyClientHandler<string, string>(cm, solver);
            auto s = MySerialServer<string,string>();
            s.open(atoi(argv[1]), c);

        }
    };
};

#endif //UNTITELD2_BOOT_H