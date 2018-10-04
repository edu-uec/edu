cmake_minimum_required(VERSION 3.12)
project(Edu_software_cpp)

set(CMAKE_CXX_STANDARD 14)

add_executable(Edu_software_cpp
        ContentMaster/ContentMasterBase_CommonMethods.cpp
        ContentMaster/TitleContentMaster.cpp
        Edu.cpp
        ContentMaster/EduContent.h
        DisplayView/EduDisplayView.h
        DisplayView/TitleDisplayView.cpp DisplayView/DisplayViewBase_CommonMethods.cpp Julius/juliusReceiver.h)
