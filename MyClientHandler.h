//
// Created by amitai on 12/01/2020.
//

#ifndef UNTITLED2_MYCLIENTHANDLER_H
#define UNTITLED2_MYCLIENTHANDLER_H
#define BUFFER_SIZE 1024
#define END_OF_COMMUNICATION "end"
#define DELIMITER '\n'

#include <strings.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sstream>
#include <algorithm>
#include "ClientHandler.h"
#include "Solver.h"
#include "CacheManager.h"

template <class Problem, class Solution>
class MyClientHandler : public ClientHandler<Problem,Solution>{
private:
    Solver<string, string> *solver;
    CacheManager<string, string> *cacheManager;

public:

    MyClientHandler(CacheManager<string, string> *cacheManager, Solver<string, string> *solver) : cacheManager(cacheManager), solver(solver) {}

    virtual void handleClient(int socket) {
        //enter into string the info from the socket
        string problem = "";
        string currentLine = "";
        string previousLine = "";
        string solution;
        char buffer[BUFFER_SIZE] = {0};
        while (true)
        {
            unsigned int i = 0;
            for (; i < BUFFER_SIZE; ++i) {
                buffer[i] = '\0';

            }
            ssize_t numBytesRead = recv(socket, buffer, BUFFER_SIZE, 0);
            if (numBytesRead > 0) {
                string check = buffer;
                stringstream ss(check);
                cout<<buffer<<endl;
                /*string delimiterBackSlashN = "\n";
                size_t posOfAllText = 0;
                string tokenOfAllText;
                while ((posOfAllText = check.find(delimiterBackSlashN)) != string::npos) {
                    tokenOfAllText = check.substr(0, posOfAllText);

                    if (!previousLine.empty()) {
                        previousLine += currentLine;
                        currentLine = previousLine;
                        previousLine = "";
                    }
                    if (currentLine == END_OF_COMMUNICATION) {
                        if (cacheManager->isSavedSolution(problem)) {
                            solution = cacheManager->getSolution(problem);
                        }
                        else {
                            solution = solver->solve(problem);
                            cacheManager->saveSolution(problem, solution);
                        }
                        write(socket, solution.c_str(), solution.length());
                        close(socket);
                        return;
                    }
                    problem += currentLine + DELIMITER;
                    check.erase(0, posOfAllText + delimiterBackSlashN.length());
                }*/
                ssize_t lineAmount = count(check.begin(), check.end(), DELIMITER);
                for (ssize_t i = 0; i < lineAmount; ++i) {
                    getline(ss, currentLine, DELIMITER);
                    if (!previousLine.empty()) {
                        previousLine += currentLine;
                        currentLine = previousLine;
                        previousLine = "";
                    }
                    if (currentLine == END_OF_COMMUNICATION) {
                        if (cacheManager->isSavedSolution(problem)) {
                            solution = cacheManager->getSolution(problem);
                        }
                        else {
                            solution = solver->solve(problem);
                            cacheManager->saveSolution(problem, solution);
                        }
                        write(socket, solution.c_str(), solution.length());
                        close(socket);
                        return;
                    }
                    problem += currentLine + DELIMITER;
                }
                //if we have half a line, save it
                if (getline(ss, currentLine, DELIMITER))
                    previousLine += currentLine;
            }
        }
    }

    ~MyClientHandler() {
        delete cacheManager;
        delete solver;
    }
};


#endif //UNTITLED2_MYCLIENTHANDLER_H
