#include <iostream>
#include <thread>
#include <unistd.h>
#include <sys/stat.h>
#include "ContentMaster/EduContent.h"
#include "Julius/juliusReceiver.h"

using namespace std;

int main(){

    //julius起動

    juliusReceiver julius;
    std::thread thread_julius([&julius]() { julius.receiveData(); });
    thread_julius.detach();
     /*
    remove("/tmp/FIFO");
    char path[256];
    if ( mkfifo("/tmp/FIFO",0666) == -1 ) { perror("mkfifo"); return 0; }

    system("./../Julius/juliusReceiver &");
    */

    TitleContentMaster tcm;

    //std::thread thread1(&TitleContentMaster::update, &tcm);

    while (1) {
        tcm.update();
        sleep(1);
    }

  return 0;
}
