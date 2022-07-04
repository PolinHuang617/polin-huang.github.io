#include <iostream>
#include <boost/coroutine2/all.hpp>

int main() {
    typedef boost::coroutines2::coroutine<int> coro_t3;
    std::cout << "start corotine" << std::endl;
    coro_t3::push_type sink([&](coro_t3::pull_type& source) {
        int num;
        num = source.get();
        std::cout << "source1: " << num << std::endl;
        source();
        std::cout << "source2: " << num << std::endl;
        source();
        std::cout << "source3: " << num << std::endl;
        source();
    });

    std::cout << "start while" << std::endl;
    int i = 1;
    while(sink) {
        std::cout << "move to coro func " << i << std::endl;
        sink(i);
        std::cout << "back from coro func " << i << std::endl;
        i++;
    }

    return 0;
}
