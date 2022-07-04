#include <boost/asio/io_context.hpp>
#include <iostream>
#include <vector>

#define BOOST_ASIO_NO_DEPRECATED
#include <boost/asio.hpp>
#include <boost/progress.hpp>

// Executed function
template <typename Iterator, typename T>
void accum(Iterator first, Iterator last, T &sum) {
    sum = 0;
    for (; first != last; ++first) {
        auto k = sqrtf(*first);
        int i = 0;
        for (i = 2; i <= k; ++i) {
            if ((*first) % i == 0) { break; }
        }
        if (i > k) { ++sum; }
    }
}

int main() {
    using namespace std::chrono_literals;
    boost::progress_timer pt;
    boost::asio::io_context io;
    boost::asio::high_resolution_timer t(io, 1ms);

    int sum = 0;
    t.async_wait([&sum](const boost::system::error_code &e) {
        boost::progress_timer pt1;
        for (std::size_t i = 1; i < 5010000; ++i) {
            auto k = sqrtf(i);
            int j = 0;
            for (j = 2; j <= k; ++j) {
                if (i % j == 0) { break; }
            }
                if (j > k) { ++sum; }
        }
        std::cout << "1. sum: " << sum << ", time spent: " << pt1.elapsed() << std::endl;
    });

    sum = 0;
    boost::progress_timer pt2;
    std::vector<int> vI;
    for (std::size_t i = 1; i < 5010000; ++i) {
        vI.push_back(i);
    }
 
    accum(vI.begin(), vI.end(), sum);
    std::cout << "2. sum: " << sum << ", time spent: " << pt2.elapsed() << std::endl;

    io.run();

    std::cout << "Total time spent: " << pt.elapsed() << std::endl;

    return 0;
}
