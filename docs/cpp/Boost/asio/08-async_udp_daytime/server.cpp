#include <iostream>
#include <ctime>
#include <string>
#include <array>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>

using boost::asio::ip::udp;

auto makeDaytimeString() -> std::string
{
    using namespace std;
    time_t now = time(0);
    return ctime(&now);
}

class udpServer
{
public:
    udpServer(boost::asio::io_context& io_context)
        : socket_(io_context, udp::endpoint(udp::v4(), 13))
    {
        startReceive();
    }

private:
    void startReceive()
    {
        socket_.async_receive_from(
                boost::asio::buffer(recv_buffer_),
                remote_endpoint_,
                boost::bind(&udpServer::handleReceive, this,
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred)
        );
    }

    void handleReceive(const boost::system::error_code& error, std::size_t size)
    {
        if (!error)
        {
            boost::shared_ptr<std::string> msg(new std::string(makeDaytimeString()));

            socket_.async_send_to(boost::asio::buffer(*msg),
                    remote_endpoint_,
                    boost::bind(&udpServer::handleSend, this,
                    msg, boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));
            startReceive();
        }
    }

    void handleSend(boost::shared_ptr<std::string> msg,
            const boost::system::error_code& error,
            std::size_t size) {}

    udp::socket socket_;
    udp::endpoint remote_endpoint_;
    std::array<char, 1> recv_buffer_;
};

auto main() -> int
{
    try
    {
        boost::asio::io_context io_context;
        udpServer server(io_context);
        io_context.run();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return EXIT_SUCCESS;
}
