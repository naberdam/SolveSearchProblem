//
// Created by amitai on 10/01/2020
//


#ifndef SOLIDPROJECT_EX2_MYTESTCLIENTHANDLER_H
#define SOLIDPROJECT_EX2_MYTESTCLIENTHANDLER_H

#include <iostream>
#include <string>
#include <unistd.h>
#include <vector>
#include <sys/socket.h>
#include <cstring>

#include "Solver.h"
#include "Server.h"
#include "CacheManager.h"
#include "Convertor.h"
#include "ClientHandler.h"
#include "FileCacheManager.h"
using namespace std;


template <typename Problem, typename Solution>
class MyTestClientHandler : public ClientHandler<Problem,Solution> {
    Solver<Problem, Solution>* solver;
    CacheManager<Problem, Solution>* cm;
public:
    MyTestClientHandler(CacheManager<Problem, Solution> *cm1, Solver<Problem,Solution>* solver1 ) {
        this->cm = cm1;
        this->solver = solver1;
    }
    void handleClient(int socket) {
        char buffer[2900];
        while (server_side::isConnecting) {
            read(socket, buffer, 1024);
            string prob(buffer);
            for (int i = 0; i < sizeof(buffer); i++) {
                buffer[i] = '\0';
            }
            if (!strcmp(prob.c_str(), "end\r\n")) {
                //GlobalShouldStop = true;
                close(socket);
                break;
            }
            if (prob.size() > 0) {
                string ans;
                if (this->cm->isSavedSolution(prob)) {
                    cout << "save solution" << endl;
                    ans = this->cm->getSolution(prob);
                } else {
                    cout << "we dont have solution" << endl;
                    ans = this->solver->solve(prob);
                    this->cm->saveSolution(prob, ans);
                }
                send(socket, ans.c_str(), ans.size(), 0);
            }
        }
    }

    ~MyTestClientHandler() {
        delete(cm);
        delete(solver);
    }

};


/*template <class P, class S>
class MyTestClientHandler : public ClientHandler<P,S> {
    Convertor<P,S> *convertor;
    Solver<P,S> *solver;
    CacheManager<P,S> *cacheManager;
public:
    MyTestClientHandler(Convertor<P,S> *convertor1, Solver<P,S> *solver1, CacheManager<P,S> *cacheManager1) {
        convertor = convertor1;
        solver = solver1;
        cacheManager = cacheManager1;
    }
    void handleClient(int socket)  {
        S solution;
        P convertedProblem;
        string line, convertedSolution;
        vector<string> problem;
        char buffer[2];
        bool isFirstLine, stop = false, foundInFile = true;
        int dataLines, lineIndex;
        while (true) {
            dataLines = 3;
            isFirstLine = true;
            lineIndex = 0;
            do {
                bzero(buffer, 2);
                line = "";
                int bytesRead;
                do {
                    bytesRead = read(socket, buffer, 1);
                    if (bytesRead < 0) {
                        if (errno == EWOULDBLOCK) {
                            continue;
                        }
                        __throw_bad_exception();
                    }
                    line += buffer[0];
                } while (buffer[0] != *"\n" && buffer[0] != *"\r\n");
                if (line == "end\n" || line == "end\r\n") {
                    stop = true;
                    break;
                } else if (isFirstLine) {
                    isFirstLine = false;
                    for (int i = 0; i < line.size(); i++) {
                        if (line[i] == ',') {
                            dataLines++;
                        }
                    }
                    problem.clear();
                }
                problem.push_back(line.substr(0, line.size() - 1));
                lineIndex++;
            } while (lineIndex != dataLines);
            if (stop) {
                break;
            }
            convertedProblem = convertor->conVecStringToProblem(problem);
            if (cacheManager->isExistProb(convertedProblem)) {
                solution = cacheManager->getSol(convertedProblem);
            } else {
                solution = solver->solve(convertedProblem);
                foundInFile = false;
            }
            convertedSolution = convertor->conSolvToString(solution);
            if (!foundInFile) {
                cacheManager->savePS(convertedProblem, convertedSolution);
            }
            if (write(socket, convertedSolution.c_str(), (int)(convertedSolution.length())) < 0) {
                throw "error writing data to socket";
            }
        }
        close(socket);
    }
};*/

#endif //SOLIDPROJECT_EX2_MYTESTCLIENTHANDLER_H
