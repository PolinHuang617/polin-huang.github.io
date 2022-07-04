#include <iostream>
#include <ctime>
#include <string>
#include <memory>
#include <boost/asio.hpp>
#include <boost/shared_array.hpp>
#include <boost/bind/bind.hpp>
#include <boost/enable_shared_from_this.hpp>

using boost::asio::ip::tcp;

auto makeDaytimeStirng() -> std::string
{
    using namespace std;  // For time_t, time and ctime;
    time_t now = time(0);
    return ctime(&now);
}

class tcpConnection :
    public boost::enable_shared_from_this<tcpConnection>
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
        message_ = makeDaytimeStirng();

        boost::asio::async_write(
            socket_,
            boost::asio::buffer(message_),
            boost::bind(
                &tcpConnection::handleWrite,
                shared_from_this(), 
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred
            )
        );
    }

private:
    tcpConnection(boost::asio::io_context& io_context)
        : socket_(io_context) {}

    void handleWrite(const boost::system::error_code& e, std::size_t size) {}

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
        acceptor_.async_accept(
            newConnection->socket(),
            boost::bind(
                &tcpServer::handleAccept, this, 
                newConnection, 
                boost::asio::placeholders::error
            )
        );
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

auto main(int argc, char** argv) -> int
{
    try
    {
        boost::asio::io_context io_context;
        tcpServer server(io_context);
        io_context.run();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return EXIT_SUCCESS;
}
