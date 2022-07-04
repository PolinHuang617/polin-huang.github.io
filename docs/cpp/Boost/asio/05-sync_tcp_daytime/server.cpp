#include <iostream>
#include <ctime>
#include <string>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

auto makeDaytimeStirng() -> std::string
{
    using namespace std;  // For time_t, time and ctime;
    time_t now = time(0);
    return ctime(&now);
}

auto main(int argc, char** argv) -> int
{
    try
    {
        boost::asio::io_context io_context;
        tcp::acceptor acceptor(io_context,
                               tcp::endpoint(tcp::v4(), 13));

        for (;;)
        {
            tcp::socket socket(io_context);
            acceptor.accept(socket);

            std::string msg = makeDaytimeStirng();

            boost::system::error_code ignored_error;
            boost::asio::write(socket,
                               boost::asio::buffer(msg),
                               ignored_error);
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return EXIT_SUCCESS;
}
