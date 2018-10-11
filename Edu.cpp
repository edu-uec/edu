#include <iostream>
#include <thread>
#include <unistd.h>
#include "ContentMaster/EduContent.h"
#include "DisplayView/EduDisplayView.h"
#include "Julius/juliusReceiver.h"

using namespace std;

int main(){

    //julius起動
    juliusReceiver julius;
    //std::thread thread1(&juliusReceiver::receiveData, &julius);
    std::thread thread_julius([&julius]() { julius.receiveData(); });

    thread_julius.detach();

    TitleContentMaster tcm;
    TitleDisplayView tdv;

    //std::thread thread1(&TitleContentMaster::update, &tcm);

    while (1) {
        tcm.update();
        tdv.update();
        sleep(1);
    }


  return 0;
}
