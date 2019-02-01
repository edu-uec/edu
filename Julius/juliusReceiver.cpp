#include <iostream>
#include "juliusReceiver.h"
#include "juliusOrder.h"

#include "client/unix_socket_client.hpp"

/*
int main(int argc, char* argv[]){
    char dir[255];
    getcwd(dir,255);
    cout<<"Current Directory : "<<dir<<endl;

    juliusReceiver julius;

    julius.receiveData();

    return 0;
}
 */

int isDelimiter(char p, char delim){
    return p == delim;
}

int split(char *dst[], char *src, char delim){
    int count = 0;

    for(;;) {
        while (isDelimiter(*src, delim)){
            src++;
        }

        if (*src == '\0') break;

        dst[count++] = src;

        while (*src && !isDelimiter(*src, delim)) {
            src++;
        }

        if (*src == '\0') break;

        *src++ = '\0';
    }
    return count;
}

juliusReceiver::juliusReceiver() {
    //julius起動
    //system("cd ../");
    system("bash ../Julius/julius_start.sh");

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
    if (connect( sockfd, (struct sockaddr *)&addr, sizeof( addr ) ) != 0){
        perror("connect fallita");
        exit(2);
    }
}

//juliusデータ受信・ソケットデータ送信、スレッド起動想定
void juliusReceiver::receiveData() {
//    asio::io_service io_service;
//    unlink("/tmp/unix_socket_test");
//    UnixSocketServer unixSocketServer1(io_service);
//    unixSocketServer1.accept();

    asio::io_service io_service;
    UnixSocketClient unixSocketClient1(io_service);
    unixSocketClient1.connect();

    preOrder.word = "";
    preOrder.CM = 0;
    preOrder.classid = 9999;

    while( julius_LOOP ) {
        sleep(1);
        rsize = recv( sockfd, buf, sizeof( buf ), 0 );

        if ( rsize == -1 ) {
            perror( "recv" );
        } else {

            rline = split(bbuf, buf, '\n');

            for(int i = 0; i < rline; i++){
                sbuf = string(bbuf[i]);
                if(sbuf.find("WHYPO WORD") != -1){
                    try {
                        char* rbbuf = bbuf[i];

                        //word取得
                        rbbuf += 17;
                        unsigned int wcount = 0;
                        while (*rbbuf++ != '"'){
                            wcount++;
                        }
                        nowOrder.word = sbuf.substr(17, wcount);

                        //classid取得
                        rbbuf += 10;
                        unsigned int icount = 0;
                        while (*rbbuf++ != '"'){
                            icount++;
                        }
                        nowOrder.classid = atoi(sbuf.substr(28 + wcount, icount).c_str()) ;

                        //cm取得
                        for(int i = 3; i > 0; rbbuf++){
                            if(*rbbuf == '"'){
                                i--;
                            }
                            wcount++;
                        }
                        nowOrder.CM = (float)(atof(sbuf.substr(30 + wcount, 5).c_str()));

                        //ソケットデータ送信
                        if(juliusReceiver::canSendData(nowOrder, preOrder)){
                            unixSocketClient1.write(nowOrder.word + "!");
                        }

                        //デバッグ用出力
                        std::cout << "julius: " << nowOrder.word << "  cid: " << nowOrder.classid << "  cm: " <<  nowOrder.CM << std::endl;


                        //保存データの更新
                        preOrder.word = nowOrder.word;
                        preOrder.classid = nowOrder.classid;
                        preOrder.CM = nowOrder.CM;
                    }catch (char *str){
                        cout << str << endl;
                        cout << "Julius recv error!: It may be caused by corruption of data.";
                    }

                }


            }
        }
    }
}

void juliusReceiver::closeSocket(){
    // ソケットクローズ
    close( sockfd );
}

char* juliusReceiver::getBuf() {
    return buf;
}

void juliusReceiver::changeLoop(int LOOP) {
    julius_LOOP = LOOP;
}

bool juliusReceiver::canSendData(Order nowOrder, Order preOrder) {
    char c = nowOrder.word.at(0);
    return (nowOrder.CM > cmMinFilter) && (c != 's') && (c != 'e') && (c != 'g');
}
