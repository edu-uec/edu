#include <iostream>
#include <string>
#include "unix_socket_client.hpp"

int main()
{
    asio::io_service io_service;

    UnixSocketClient unixSocketClient1(io_service);
    unixSocketClient1.connect();
    for(int i=0; true; i++){
        unixSocketClient1.read();
    }
}
