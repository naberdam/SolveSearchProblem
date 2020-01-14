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
#include "MatrixBuilder.h"
#include "MyMatrixSearchable.h"

template <class T>
class MyClientHandler : public ClientHandler{
private:
    Solver<Searchable<T>*, string> *solver;
    CacheManager<string, string> *cacheManager;

public:

    MyClientHandler(CacheManager<string, string> *cacheManager, Solver<Searchable<T>*, string> *solver) : cacheManager(cacheManager), solver(solver) {}

    virtual void handleClient(int socket) {
        //enter into string the info from the socket
        string problem = "";
        string currentLine = "";
        string previousLine = "";
        string solution;
        char buffer[BUFFER_SIZE] = {0};
        vector<vector<double>> detailsOnMatrix;
        while (true)
        {
            unsigned int k = 0;
            for (; k < BUFFER_SIZE; ++k) {
                buffer[k] = '\0';

            }
            ssize_t numBytesRead = recv(socket, buffer, BUFFER_SIZE, 0);
            if (numBytesRead > 0) {
                string check = buffer;
                stringstream ss(check);
                cout<<buffer<<endl;
                ssize_t lineAmount = count(check.begin(), check.end(), DELIMITER);
                string endStr = check.substr(0, 3);
                if (!strcmp(endStr.c_str(), "end")) {
                    break;
                }
                check += "\n";
                detailsOnMatrix.push_back(addLineAfterParsingByComaToVector(check));
                problem += check;
            }
        }
        MyMatrixSearchable* matrixSearchable = MatrixBuilder::createMatrix(detailsOnMatrix, problem);
        if (this->cacheManager->isSavedSolution(problem)) {
            cout << "save solution" << endl;
            solution = this->cacheManager->getSolution(problem);
        } else {
            cout << "we dont have solution" << endl;
            solution = this->solver->solve(matrixSearchable);
            this->cacheManager->saveSolution(problem, solution);
        }
    }

    string deleteSpacesFromLine(string line) {
        unsigned int i = 0;
        string stringWithoutSpaces;
        for (; i < line.size(); ++i) {
            if (line[i] == ' ') {
                continue;
            }
            stringWithoutSpaces += line[i];
        }

        return stringWithoutSpaces;
    }

    vector<double> addLineAfterParsingByComaToVector(const string line) {
        string lineTemp = deleteSpacesFromLine(line);
        string delimiterOfAllText = ",";
        size_t posOfAllText = 0;
        string tokenOfAllText;
        vector<double> cellInVectorOfAllMatrix;
        unsigned int i = 0;
        while ((posOfAllText = lineTemp.find(delimiterOfAllText)) != string::npos) {
            tokenOfAllText = lineTemp.substr(0, posOfAllText);
            lineTemp.erase(0, posOfAllText + delimiterOfAllText.length());
            cellInVectorOfAllMatrix.push_back(stod(tokenOfAllText));
        }
        posOfAllText = lineTemp.find("\n");
        tokenOfAllText = lineTemp.substr(0, posOfAllText);
        cellInVectorOfAllMatrix.push_back(stod(tokenOfAllText));
        return cellInVectorOfAllMatrix;
    }

    ~MyClientHandler() {
        delete cacheManager;
        delete solver;
    }
};


#endif //UNTITLED2_MYCLIENTHANDLER_H