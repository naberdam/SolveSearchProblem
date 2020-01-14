//
// Created by amitai on 10/01/2020
//


#ifndef SOLIDPROJECT_EX2_MYSERIALSERVER_H
#define SOLIDPROJECT_EX2_MYSERIALSERVER_H

#include <pthread.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <iostream>
#include <thread>

#include "Server.h"
#include "ClientHandler.h"

using namespace std;

template<class P, class S>
static void *start(int port, ClientHandler *clientHandler) {
    int sockfd, newsockfd;
    struct sockaddr_in serv_addr;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    /* Check of creation succeeded*/
    if (sockfd < 0) {
        perror("Failed to open connection.");
        exit(1);
    }

    // Initialize m_socket structure
    bzero((char *) &serv_addr, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons((uint16_t) ((size_t) port));

    // Now bind the host address using bind() call.
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("Failed to bind server connection.");
        exit(1);
    }
    timeval timeout;
    timeout.tv_sec = 10;
    timeout.tv_usec = 0;
    setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (char *) &timeout, sizeof(timeout));

    while (server_side::isConnecting) {
        listen(sockfd, 20000);
        struct sockaddr_in cli_addr;
        socklen_t clilen = sizeof(cli_addr);
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, (socklen_t *) &clilen);

        if (newsockfd < 0) {
            if (errno == EWOULDBLOCK) {
                cout << "timeout!" << endl;
                server_side::isConnecting = false;
                break;
            } else {
                perror("other error");
                server_side::isConnecting = false;
                break;
            }
        }
        clientHandler->handleClient(newsockfd);
    }
}


template<class P, class S>
class MySerialServer : public server_side::Server<P, S> {
public:
    virtual void open(int port, ClientHandler *clientHandler) {
        server_side::isConnecting = true;
        thread thr1(start<P, S>, port, clientHandler);
        thr1.detach();

    }


    virtual void stop() {
        server_side::isConnecting = false;
    }
};

#endif //SOLIDPROJECT_EX2_MYSERIALSERVER_H
