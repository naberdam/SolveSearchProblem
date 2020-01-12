//
// Created by amitai on 10/01/2020
//


#ifndef PROJECT2_CLIENTHANDLER_H
#define PROJECT2_CLIENTHANDLER_H

#include <string>
#include <iostream>

using namespace std;
template <class P, class S>
class ClientHandler {
public:
    virtual void handleClient(int socket) = 0;
};


#endif //PROJECT2_CLIENTHANDLER_H
