#include <iostream>
#include <array>
#include <boost/asio.hpp>

using boost::asio::ip::udp;

auto main(int argc, char* argv[]) -> int
{
    try
    {
        if (argc != 2)
        {
            std::cerr << "Usage: client <host>" << std::endl;
            return EXIT_FAILURE;
        }

        boost::asio::io_context io_context;

        udp::resolver resolver(io_context);
        udp::endpoint reciever_endpoint =
            *resolver.resolve(udp::v4(), argv[1], "daytime").begin();
        udp::socket socket(io_context);
        socket.open(udp::v4());

        std::array<char, 1> send_buf = {{0}};
        socket.send_to(boost::asio::buffer(send_buf), reciever_endpoint);

        std::array<char, 128> recv_buf;
        udp::endpoint sender_endpoint;
        std::size_t len = socket.receive_from(
                boost::asio::buffer(recv_buf), sender_endpoint);

        std::cout.write(recv_buf.data(), len);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return EXIT_SUCCESS;
}
