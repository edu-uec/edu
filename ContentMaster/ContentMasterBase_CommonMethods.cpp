#include <iostream>

#include "EduContent.h"

using namespace std;

void ContentMasterBase::update() {
    cout << "cm" << endl;
}

void ContentMasterBase::call() {
    cout << "called" << endl;
}