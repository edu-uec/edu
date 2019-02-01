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
#include "juliusOrder.h"

using namespace std;

#define PORT 10500
#define HOST "127.0.0.1" //localhost
#define cmMinFilter 0.7 //CM値による送信制御の闘値

int isDelimiter(char p, char delim);

int split(char *dst[], char *src, char delim);

class juliusReceiver{
public:
    juliusReceiver();

    void receiveData();

    void closeSocket();

    char* getBuf();

    void changeLoop(int LOOP);

    bool canSendData(Order nowOrder, Order preOrder);

private:
    int sockfd;
    struct sockaddr_in addr = {0,};
    string sbuf;
    int julius_LOOP = 1;

    Order preOrder, nowOrder;//前回周の命令と現在の命令

    // 受信
    int rsize;
    char buf[1024];
    char *bbuf[100];
    int rline;
};

#endif //EDU_SOFTWARE_CPP_JULIUSRECEIVER_H
