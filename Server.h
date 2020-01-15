//
// Created by amitai on 10/01/2020
//


#ifndef PROJECT2_SERVER_H
#define PROJECT2_SERVER_H

#include "ClientHandler.h"

namespace server_side {
    static bool isConnecting = true;

    template<class Problem, class Solution>
    class Server {
    public:
        //open the server in the port and wait for the customer - connection
        virtual void open(int port, ClientHandler *c) = 0;

        //close the server
        virtual void stop() = 0;

        virtual ~Server() {}
    };
}


#endif //PROJECT2_SERVER_H



