//
// Created by amitai on 10/01/2020
//


#ifndef PROJECT2_SERVER_H
#define PROJECT2_SERVER_H

#include "ClientHandler.h"

namespace server_side {
    static bool isConnecting = true;
    template<class P, class S>
    class Server {
    protected:
        bool shouldStop = false;
    public:
        //open the server in the port and wait for the customer - connection
        virtual void open(int port, ClientHandler<P,S>* c) = 0;

        //close the server
        virtual void stop() = 0;
    };
}


#endif //PROJECT2_SERVER_H



