#include <cmath>
#include <unistd.h>
#include <boost/progress.hpp>
#include "threadpool.h"

void mytask(int i) {
    printf("Info: thread %ld is working on task %d\n", (u_int64_t)pthread_self(), i);
    sleep(1);
    return;
}

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

int accum1(std::vector<int>::iterator first, std::vector<int>::iterator last, int& sum) {
    sum = 0;
    for (; first != last; ++first) {
        auto k = sqrtf(*first);
        int i = 0;
        for (i = 2; i <= k; ++i) {
            if ((*first) % i == 0) { break; }
        }
        if (i > k) { ++sum; }
    }
    return sum;
}

int main() {
    constexpr int SIZE = 50100000;
    constexpr int threadSIZE = 7;
    constexpr int blockSize = SIZE / threadSIZE;
    
    std::vector<int> vI;
    for (std::size_t i = 1; i < SIZE; ++i) {
        vI.push_back(i);
    }

    ThreadPool threadpool(threadSIZE);
    /*for (int i = 0; i < 100; ++i) {
        threadpool.enqueue(mytask, i);
    }*/

    {
        int sum = 0;
        auto begin = vI.begin();
        std::vector<std::future<int>> vf;
        boost::progress_timer pt;
        for (size_t i = 0; i < threadSIZE - 1; ++i)
        {
            auto end = begin;
            std::advance(end, blockSize);
            vf.emplace_back(threadpool.enqueue(accum1, begin, end, sum));
            // sum += t.get();
            //std::cout << "1. sum: " << t.get() << ", time spent: ";
            begin = end;
        }
        vf.emplace_back(threadpool.enqueue(accum1, begin, vI.end(), sum));
        for (auto& f : vf) { sum += f.get(); }
        std::cout << "1. sum: " << sum << ", time spent: ";
    }


    {
        int sum = 0;
        boost::progress_timer pt;
        accum(vI.begin(), vI.end(), sum);
        std::cout << "2. sum: " << sum << ", time spent: ";
    }
 
    return 0;
}
