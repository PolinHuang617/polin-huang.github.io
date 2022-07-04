#include <iostream>
#include <ctime>
#include <string>
#include <array>
#include <boost/asio.hpp>

using boost::asio::ip::udp;

auto makeDaytimeString() -> std::string
{
    using namespace std;
    time_t now = time(0);
    return ctime(&now);
}

auto main() -> int
{
    try
    {
        boost::asio::io_context io_context;
        udp::socket socket(io_context, udp::endpoint(udp::v4(), 13));

        for (;;)
        {
            std::array<char, 1> recv_buf;
            udp::endpoint remote_endpoint;
            socket.receive_from(boost::asio::buffer(recv_buf), remote_endpoint);

            std::string msg = makeDaytimeString();

            boost::system::error_code ignored_error;
            socket.send_to(boost::asio::buffer(msg),
                    remote_endpoint, 0, ignored_error);
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return EXIT_SUCCESS;
}
