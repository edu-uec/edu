#ifndef UNIX_SOCKET_SERVER_HPP
#define UNIX_SOCKET_SERVER_HPP

#include <boost/asio.hpp>
#include <iostream>

namespace asio = boost::asio;
using asio::local::stream_protocol;

class UnixSocketServer
{
  private:
    asio::io_service &io_service_;
    stream_protocol::socket socket_;
    stream_protocol::acceptor acceptor_;

  public:
    UnixSocketServer(asio::io_service &io_service)
        : io_service_(io_service),
          socket_(io_service),
          acceptor_(io_service, stream_protocol::endpoint("/tmp/unix_socket_test"))
    {
    }
    void accept()
    {
        acceptor_.accept(socket_);
    }

    void write(std::string msg1)
    {
        const std::string msg = msg1 + ",";

        std::cout <<  msg << std::endl;
        std::cout << msg1 << std::endl;

        boost::system::error_code error;
        asio::write(socket_, asio::buffer(msg), error);

        if (error) {
            std::cout << "send failed: " << error.message() << std::endl;
        }
        else {
            std::cout << "send correct!" << std::endl;
        }
    }
};

#endif