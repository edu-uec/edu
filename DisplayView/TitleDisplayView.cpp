//
// Created by 松田尚也 on 2018/09/20.
//
#include <iostream>
#include <unistd.h>
#include "EduDisplayView.h"

using namespace std;

void TitleDisplayView::update() {
    while (update_LOOP){
        cout << "tdv update\n" << endl;
        sleep(1);
    }
}