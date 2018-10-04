#include <iostream>
#include <thread>
#include <unistd.h>
#include "ContentMaster/EduContent.h"
#include "DisplayView/EduDisplayView.h"
#include "Julius/juliusReceiver.h"

using namespace std;

int main(int argc, char* argv[]){

    //julius起動
    juliusReceiver julius;
    //std::thread thread1(&juliusReceiver::receiveData, &julius);
    std::thread thread_julius([&julius]() { julius.receiveData(); });

    thread_julius.detach();


    TitleContentMaster tcm;
    TitleDisplayView tdv;

    //std::thread thread1(&TitleContentMaster::update, &tcm);
    std::thread thread1([&tcm, &tdv]() {
        while (1) {
            tcm.update();
            tdv.update();
            sleep(1);
        }
    });
    thread1.join();//join関数ならば合流を待つ。 detach関数ならば合流を待たない。

  return 0;
}
