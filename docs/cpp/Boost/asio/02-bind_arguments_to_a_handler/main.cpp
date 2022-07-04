#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>

using namespace std::chrono_literals;

void print(const boost::system::error_code& e,
           boost::asio::steady_timer* t,
           int* count) {

    if (*count < 10) {
        std::cout << *count << std::endl;
        ++(*count);

        t->expires_at(t->expiry() + 1s);
        t->async_wait(boost::bind(print,
                    boost::asio::placeholders::error,
                    t,
                    count));
    }
}

int main() {
    boost::asio::io_context io;
    int count = 0;
    boost::asio::steady_timer t(io, 1s);
    t.async_wait(boost::bind(print,
                boost::asio::placeholders::error,
                &t,
                &count));

    io.run();

    std::cout << "Final count is " << count << std::endl;

    return EXIT_SUCCESS;
}
