cmake_minimum_required(VERSION 3.7)
project(Edu_software_cpp)

set(CMAKE_C_COMPILER /usr/bin/gcc)
set(CMAKE_CXX_COMPILER /usr/bin/g++)
set(CMAKE_CXX_STANDARD 14)
set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(Boost REQUIRED COMPONENTS system filesystem)
find_package(Threads REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})
message("## Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")

add_executable(Edu_software_cpp
        ContentMaster/ContentMasterBase_CommonMethods.cpp
        ContentMaster/TitleContentMaster.cpp
        Edu.cpp
        ContentMaster/EduContent.h
        Julius/structOrder.h Julius/server/unix_socket_server.hpp
        Julius/juliusReceiver.h Julius/juliusReceiver.cpp)

target_link_libraries(Edu_software_cpp Boost::system pthread Threads::Threads)
