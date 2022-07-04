#include <iostream>
#include <boost/asio.hpp>

void print(const boost::system::error_code &e)
{
    std::cout << "Hello, world!" << std::endl;
}

auto main() -> int
{
    using namespace std::chrono_literals;

    boost::asio::io_context io;
    boost::asio::steady_timer t(io, 5s);

    // Suspending here to wait time out.
    t.async_wait(&print);

    std::cout << "main thread: Hello, world!" << std::endl;

    io.run();

    return EXIT_SUCCESS;
}
