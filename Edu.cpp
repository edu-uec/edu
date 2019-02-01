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
    thread_julius.join();

  return 0;
}
