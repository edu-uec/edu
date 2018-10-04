#include <iostream>
#include <unistd.h>
#include "EduContent.h"

using namespace std;

//ヘッダファイルに書いていないメソッドやクラスは他のファイルからは隠される
string methodTest(){
    return "tcm update\n";
}

void TitleContentMaster::update() {
    cout << methodTest() << endl;
}

