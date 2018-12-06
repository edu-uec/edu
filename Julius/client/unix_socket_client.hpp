#ifndef UNIX_SOCKET_CLIENT_HPP
#define UNIX_SOCKET_CLIENT_HPP

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <iostream>

namespace asio = boost::asio;
using asio::local::stream_protocol;

class UnixSocketClient
{
  private:
    asio::io_service &io_service_;
    stream_protocol::socket socket_;
    boost::system::error_code error;

    asio::streambuf receive_buff_;

  public:
    UnixSocketClient(asio::io_service &io_service)
        : io_service_(io_service),
          socket_(io_service)
    {
    }
    void connect()
    {

        socket_.connect(stream_protocol::endpoint("/tmp/unix_socket_test"));
    }

    void read()
    {
        if (asio::read_until(socket_, receive_buff_, ',', error))
        {

            if (error && error != asio::error::eof)
            {
                std::cout << "receive failed: " << error.message() << std::endl;
            }
            else
            {
                const char *data = asio::buffer_cast<const char *>(receive_buff_.data());
                std::cout << data << std::endl;
            }
            receive_buff_.consume(receive_buff_.size());
        }
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