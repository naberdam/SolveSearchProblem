//
// Created by amitai on 12/01/2020.
//

#ifndef UNTITLED2_MYCLIENTHANDLER_H
#define UNTITLED2_MYCLIENTHANDLER_H
#define BUFFER_SIZE 4000

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

template<class T>
class MyClientHandler : public ClientHandler {
 private:
  CacheManager<string, string> *cacheManager;
  Solver<Searchable<T> *, string> *solver;

 public:

  MyClientHandler(CacheManager<string, string> *cacheManager1, Solver<Searchable<T> *, string> *solver1) : cacheManager(
      cacheManager1), solver(solver1) {}

  virtual void handleClient(int socket) {
    //problem will be the representation of the matrix in FileCacheManager
    string problem;
    //the current line which we will put in vector that will send to MatrixBuilder
    string currentLine;
    //solution of the problem
    string solution;
    char buffer[BUFFER_SIZE] = {0};
    //vector of all lines that we will receive from server
    vector<vector<double>> detailsOnMatrix;
    //boolean that represents if we already got "end" from server
    bool endOfMatrix = false;
    //as long as current line is not "end"
    while (!endOfMatrix) {
      unsigned int k = 0;
      //flush the buffer
      for (; k < BUFFER_SIZE; ++k) {
        buffer[k] = '\0';
      }
      ssize_t numBytesRead = recv(socket, buffer, BUFFER_SIZE, 0);
      //if we got something from server
      if (numBytesRead > 0) {
        unsigned int i;
        for (i = 0; i < numBytesRead; i++) {
          char c = buffer[i];
          //end of the line
          if (c == '\n') {
            if (currentLine.length() > 0) {
              if (currentLine == "end") {
                endOfMatrix = true;
                break;
              }
              //add this line, which is currentLine, to vector of matrix without spaces and comas
              detailsOnMatrix.push_back(addLineAfterParsingByComaToVector(currentLine));
              problem += currentLine + "\n";
              currentLine.clear();
            }
          } else {
            //part of the line
            currentLine += c;
          }
        }
      }
    }
    //create the matrix using detailsOnMatrix which contains all the lines we got from server (besides "end")
    MyMatrixSearchable *matrixSearchable = MatrixBuilder::createMatrix(detailsOnMatrix, problem);
    //if we have solution for this problem
    if (this->cacheManager->isSavedSolution(problem)) {
      cout << "There is a solution" << endl;
      solution = this->cacheManager->getSolution(problem);

    } else {
      //there is no solution in cacheManager, so we need to solve it
      cout << "we dont have solution, but we will find for you" << endl;
      solution = this->solver->solve(matrixSearchable);
      this->cacheManager->saveSolution(problem, solution);
      /*cout << solution << endl;*/
    }
    cout << solution << endl;
    if (buffer[0] == '\0') {
      cout << "prob" << endl;
    }
    //write the solution to server
    write(socket, solution.c_str(), solution.length());
  }

  string deleteSpacesFromLine(string line) {
    unsigned int i;
    string stringWithoutSpaces;
    for (i = 0; i < line.size(); ++i) {
      //delete space from the line
      if (line[i] == ' ') {
        continue;
      }
      stringWithoutSpaces += line[i];
    }
    //returns line without spaces
    return stringWithoutSpaces;
  }

  vector<double> addLineAfterParsingByComaToVector(const string line) {
    string lineTemp = deleteSpacesFromLine(line);
    string delimiterOfAllText = ",";
    size_t posOfAllText = 0;
    string tokenOfAllText;
    vector<double> cellInVectorOfAllMatrix;
    //as long as there is ',' in lineTemp
    while ((posOfAllText = lineTemp.find(delimiterOfAllText)) != string::npos) {
      //take the value till the ','
      tokenOfAllText = lineTemp.substr(0, posOfAllText);
      //erase this value from lineTemp
      lineTemp.erase(0, posOfAllText + delimiterOfAllText.length());
      //add this value, which is tokenOfAllText, to the vector
      cellInVectorOfAllMatrix.push_back(stod(tokenOfAllText));
    }
    //parsing the last value in lineTemp
    posOfAllText = lineTemp.find('\n');
    tokenOfAllText = lineTemp.substr(0, posOfAllText);
    //add it to vector
    cellInVectorOfAllMatrix.push_back(stod(tokenOfAllText));
    return cellInVectorOfAllMatrix;
  }

  ~MyClientHandler() {
    delete cacheManager;
    delete solver;
  }
};

#endif //UNTITLED2_MYCLIENTHANDLER_H