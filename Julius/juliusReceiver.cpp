#include <iostream>
#include "juliusReceiver.h"

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
    system("cd ../");
    system("bash ../Julius/julius_start.sh");

    sleep(2);

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

}

void juliusReceiver::receiveData() {
    // 受信
    int rsize;
    char *bbuf[100];
    int rline;

    while( julius_LOOP ) {
        rsize = recv( sockfd, buf, sizeof( buf ), 0 );

        if ( rsize == -1 ) {
            perror( "recv" );
        } else {
            //printf("recv : %s\n", buf);
            rline = split(bbuf, buf, '\n');

            for(int i = 0; i < rline; i++){
                sbuf = string(bbuf[i]);
                if(sbuf.find("WHYPO WORD") != -1){
                    //printf("rr : %s\n", bbuf[i]);

                    //order準備初期化
                    auto order1 = (struct order*)malloc(sizeof(struct order));

                    char* rbbuf = bbuf[i];

                    //word取得
                    rbbuf += 17;
                    unsigned int wcount = 0;
                    while (*rbbuf++ != '"'){
                        wcount++;
                    }
                    order1->word = sbuf.substr(17, wcount);

                    //classid取得
                    rbbuf += 10;
                    unsigned int icount = 0;
                    while (*rbbuf++ != '"'){
                        icount++;
                    }
                    order1->classid = atoi(sbuf.substr(28 + wcount, icount).c_str()) ;


                    //cm取得
                    for(int i = 3; i > 0; rbbuf++){
                        if(*rbbuf == '"'){
                            i--;
                        }
                        wcount++;
                    }
                    order1->CM = (float)(atof(sbuf.substr(30 + wcount, 5).c_str()));

                    //デバッグ用出力
                    std::cout << "julius: " << order1->word << " " << order1->classid << " " <<  order1->CM << std::endl;

                }


            }

            /*
            // 応答
            printf( "send:%s\n", buf );
            write( sockfd, buf, rsize );
             */

            sleep(1);

        }
    }
    printf("called3");
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

