#include <iostream>
#include <array>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

auto main(int argc, char** argv) -> int
{
    try
    {
        if (argc != 2)
        {
            std::cerr << "Usage: client <host>" << std::endl;
        }

        boost::asio::io_context io_context;

        tcp::resolver resolver(io_context);
        tcp::resolver::results_type endpoints =
            resolver.resolve(argv[1], "daytime");

        tcp::socket socket(io_context);
        boost::asio::connect(socket, endpoints);

        for (;;)
        {
            std::array<char, 128> buf;
            boost::system::error_code err;
            std::size_t len = 
                socket.read_some(boost::asio::buffer(buf), err);

            if (err == boost::asio::error::eof)
            {
                break;
            }
            else if (err)
            {
                throw boost::system::system_error(err);
            }

            std::cout.write(buf.data(), len);
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return EXIT_SUCCESS;
}
