#include <iostream>
#include <functional>
#include <boost/asio.hpp>

using namespace std::chrono_literals;

class Printer {
    public:
        Printer(boost::asio::io_context &io)
            : timer_(io, 1s),
              count_(0) {
            timer_.async_wait(std::bind(&Printer::print, this));
        }

        ~Printer() {
            std::cout << "Final count is " << count_ << std::endl;
        }

        void print() {
            if (count_ < 5) {
                std::cout << count_ << std::endl;
                ++count_;

                timer_.expires_at(timer_.expiry() + 1s);
                timer_.async_wait(std::bind(&Printer::print, this));
            }
        }

    private:
        boost::asio::steady_timer timer_;
        std::size_t count_;
};

int main() {
    boost::asio::io_context io;
    Printer printer(io);

    io.run();


    return EXIT_SUCCESS;
}
