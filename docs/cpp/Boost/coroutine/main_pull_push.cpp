#include <iostream>
#include <unistd.h>
#include <boost/coroutine2/all.hpp>

int main()
{
    typedef boost::coroutines2::coroutine<std::time_t> coro_t2;

    std::cout << "start corotine" << std::endl;
    coro_t2::pull_type source([&](coro_t2::push_type& sink) {
        //std::cout << " sink1" << std::endl;
        //sink(1);
        //std::cout << " sink2" << std::endl;
        //sink(2);
        //std::cout << " sink3" << std::endl;
        //sink(3);
        while(true) {
            sleep(1);
            sink(std::time(NULL));
        }
    });

    std::cout << "start while" << std::endl;
    //while(source) {
    while(true) {
        auto ret = source.get();
        std::cout << "move to coro func" << std::ctime(&ret) << std::endl;

        std::cout << "Main thread..." << std::endl;

        source();
        std::cout << "back from coro func" << std::endl;
    }

    return 0;
}
