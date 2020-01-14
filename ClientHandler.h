//
// Created by amitai on 10/01/2020
//


#ifndef PROJECT2_CLIENTHANDLER_H
#define PROJECT2_CLIENTHANDLER_H

#include <string>
#include <iostream>

using namespace std;

class ClientHandler {
public:
    virtual ~ClientHandler() {

    }

    virtual void handleClient(int socket) = 0;
};


#endif //PROJECT2_CLIENTHANDLER_H
