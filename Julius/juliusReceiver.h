//
// Created by 松田尚也 on 2018/10/03.
//

#ifndef EDU_SOFTWARE_CPP_JULIUSRECEIVER_H
#define EDU_SOFTWARE_CPP_JULIUSRECEIVER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 10500
#define HOST "127.0.0.1" //localhost

class juliusReceiver{
public:
    juliusReceiver(){
        //julius起動
        system("cd ../");
        system("bash ../Julius/julius_start.sh");

        sleep(5);

        // ソケット生成
        if( (sockfd = socket( AF_INET, SOCK_STREAM, 0) ) < 0 ) {
            perror( "socket" );
            exit(2);
        }

        // 送信先アドレス・ポート番号設定
        addr.sin_family = AF_INET;
        addr.sin_port = htons( PORT );
        addr.sin_addr.s_addr = inet_addr( HOST );
        //addr.sin_addr.s_addr = INADDR_ANY;

        // サーバ接続
        if (connect( sockfd, (struct sockaddr *)&addr, sizeof( addr ) ) < 0){
            perror("connect fallita");
            exit(2);
        }
        /*
        // データ送信
        char send_str[10];
        char receive_str[10];
        for ( int i = 0; i < 10; i++ ){
            sprintf( send_str, "%d", i );
            printf( "send:%d\n", i );
            if( send( sockfd, send_str, 10, 0 ) < 0 ) {
                perror( "send" );
            } else {
                recv( sockfd, receive_str, 10, 0 );
                printf( "receive:%s\n", receive_str );
            }
            sleep( 1 );
        }
        */
    }

    void receiveData(){
        // 受信
        int rsize;
        while( julius_LOOP ) {
            rsize = recv( sockfd, buf, sizeof( buf ), 0 );

            if ( rsize == -1 ) {
                perror( "recv" );
            } else {
                printf( "receive:%s\n", buf );
                sleep( 1 );

                // 応答
                printf( "send:%s\n", buf );
                write( sockfd, buf, rsize );
            }
        }
        printf("called3");
    }

    void closeSocket(){
        // ソケットクローズ
        close( sockfd );
    }

    char* getBuf(){
        return buf;
    }

    void changeLoop(int LOOP){
        julius_LOOP = LOOP;
    }

private:
    int sockfd;
    struct sockaddr_in addr = {0,};
    char buf[10240];
    int julius_LOOP = 1;
};


#endif //EDU_SOFTWARE_CPP_JULIUSRECEIVER_H
