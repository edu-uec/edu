#include <iostream>
#include <thread>
#include <unistd.h>
#include "ContentMaster/EduContent.h"
#include "DisplayView/EduDisplayView.h"

using namespace std;

int main(){
  cout << "main 0" << endl;

  TitleContentMaster tcm;
  tcm.call();
  //std::thread thread1(&TitleContentMaster::update, &tcm);
  std::thread thread1([&tcm]() { tcm.update(); });
  thread1.detach();//join関数ならば合流を待つ。 detach関数ならば合流を待たない。

  TitleDisplayView tdv, tdv2;
  std::thread thread2([&tdv]() { tdv.update(); });
  thread2.detach();

  cout << "main 1" << endl;
  sleep(5);

  tdv.update_LOOP = false;

  cout << "main 2" << endl;

  sleep(5);

  return 0;
}
