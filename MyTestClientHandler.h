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
#include "ClientHandler.h"
#include "FileCacheManager.h"
using namespace std;


template <typename Problem, typename Solution>
class MyTestClientHandler : public ClientHandler {
    Solver<string, string>* solver;
    CacheManager<string, string>* cm;
public:
    MyTestClientHandler(FileCacheManager<Problem, Solution> *cm1, Solver<Problem,Solution>* solver1 ) {
        this->cm = cm1;
        this->solver = solver1;
    }
    void handleClient(int socket) {
        char buffer[4900];
        while (server_side::isConnecting) {
            read(socket, buffer, 2024);
            string prob(buffer);

            for (int i = 0; i < sizeof(buffer); i++) {
                buffer[i] = '\0';
            }
            string endStr = prob.substr(0,3);
            if (!strcmp(endStr.c_str(), "end")) {
                server_side::isConnecting = false;
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


#endif //SOLIDPROJECT_EX2_MYTESTCLIENTHANDLER_H
