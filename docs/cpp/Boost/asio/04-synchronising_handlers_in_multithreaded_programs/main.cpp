#include <iostream>
#include <thread>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>

using namespace std::chrono_literals;

class Printer
{
    public:
        Printer(boost::asio::io_context& io)
            : strand_(boost::asio::make_strand(io)),
            timer1_(io, 1s),
            timer2_(io, 1s),
            count_(0)
        {
            timer1_.async_wait(boost::asio::bind_executor(strand_, boost::bind(&Printer::print1, this)));

            timer2_.async_wait(boost::asio::bind_executor(strand_, boost::bind(&Printer::print2, this)));
        }

        ~Printer() {
            std::cout << "Final count is " << count_ << std::endl;
        }

        void print1() {
            if (count_ < 10) {
                std::cout << "Timer 1: " << count_ << std::endl;
                ++count_;

                timer1_.expires_at(timer1_.expiry() + 1s);

                timer1_.async_wait(boost::asio::bind_executor(
                            strand_,
                            boost::bind(&Printer::print1, this))
                );
            }
        }

        void print2() {
            if (count_ < 10) {
                std::cout << "Timer 2: " << count_ << std::endl;
                ++count_;

                timer2_.expires_at(timer2_.expiry() + 1s);

                timer2_.async_wait(boost::asio::bind_executor(
                            strand_,
                            boost::bind(&Printer::print2, this))
                );
            }
        }


    private:
        boost::asio::strand<boost::asio::io_context::executor_type> strand_;
        boost::asio::steady_timer timer1_;
        boost::asio::steady_timer timer2_;
        std::size_t count_;
};

int main()
{
    boost::asio::io_context io;
    Printer printer(io);

    std::thread th(boost::bind(&boost::asio::io_context::run, &io));
    io.run();
    th.join();

    return 0;
}
