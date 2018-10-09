//
// Created by 松田尚也 on 2018/10/03.
//

#ifndef EDU_SOFTWARE_CPP_JULIUSRECEIVER_H
#define EDU_SOFTWARE_CPP_JULIUSRECEIVER_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "../rapidxml-1.13/rapidxml.hpp"

using namespace std;

#define PORT 10500
#define HOST "127.0.0.1" //localhost

int isDelimiter(char p, char delim);

int split(char *dst[], char *src, char delim);
  
class juliusReceiver{
public:
    juliusReceiver();

    void receiveData();

    void closeSocket();

    char* getBuf();

    void changeLoop(int LOOP);

private:
    int sockfd;
    struct sockaddr_in addr = {0,};
    char buf[1024 * 5];
    string sbuf;
    char *buff[20];
    int julius_LOOP = 1;
};

struct order{
    string word;
    int classid;
    float CM;
};

#endif //EDU_SOFTWARE_CPP_JULIUSRECEIVER_H
