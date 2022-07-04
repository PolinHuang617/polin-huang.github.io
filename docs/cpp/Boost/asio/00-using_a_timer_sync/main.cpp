#include <iostream>
#include <boost/asio.hpp>

auto main() -> int
{
    using namespace std::chrono_literals;

    boost::asio::io_context io;
    boost::asio::steady_timer t(io, 5s);

    // Suspending here to wait time out.
    t.wait();

    std::cout << "Hello, world!" << std::endl;

    return EXIT_SUCCESS;
}
