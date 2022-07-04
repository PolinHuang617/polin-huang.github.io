#include <iostream>
#include <ctime>
#include <string>
#include <array>
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/bind/bind.hpp>

using boost::asio::ip::udp;
using boost::asio::ip::tcp;

auto makeDaytimeString() -> std::string
{
    using namespace std;
    time_t now = time(0);
    return ctime(&now);
}

class tcpConnection
    : public boost::enable_shared_from_this<tcpConnection>
{
public:
    typedef boost::shared_ptr<tcpConnection> pointer;

    static pointer create(boost::asio::io_context& io_context)
    {
        return pointer(new tcpConnection(io_context));
    }

    tcp::socket& socket()
    {
        return socket_;
    }

    void start()
    {
        message_ = makeDaytimeString();

        boost::asio::async_write(socket_, boost::asio::buffer(message_),
                boost::bind(&tcpConnection::handleWrite, shared_from_this()));
    }

private:
    tcpConnection(boost::asio::io_context& io_context)
        : socket_(io_context) {}

    void handleWrite() {}

    tcp::socket socket_;
    std::string message_;

};

class tcpServer
{
public:
    tcpServer(boost::asio::io_context& io_context)
        : io_context_(io_context),
          acceptor_(io_context, tcp::endpoint(tcp::v4(), 13))
    {
        startAccept();
    }

private:
    void startAccept()
    {
        tcpConnection::pointer newConnection =
            tcpConnection::create(io_context_);

        acceptor_.async_accept(newConnection->socket(),
                boost::bind(&tcpServer::handleAccept,
                    this, newConnection, boost::asio::placeholders::error));
    }

    void handleAccept(tcpConnection::pointer newConnection,
            const boost::system::error_code& error)
    {
        if (!error)
        {
            newConnection->start();
        }
        startAccept();
    }

    boost::asio::io_context& io_context_;
    tcp::acceptor acceptor_;
};

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
        tcpServer server1(io_context);
        udpServer server2(io_context);
        io_context.run();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return EXIT_SUCCESS;
}
