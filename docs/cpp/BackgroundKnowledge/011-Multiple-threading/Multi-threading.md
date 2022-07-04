## `std::thread threadObject(callable)`

a `callable` can be:
- pointer to function
- function object
- lambda expression

```cpp
#include <iostream>
#include <thread>

using namespace std;

auto foo(int z) -> void {
    for (size_t i = 0; i < z; ++i)
        cout << "Callable function" << endl;
}

class thread_obj {
public:
    auto operator()(int x) -> void {
        for (size_t i = 0; i < x; ++i)
            cout << "Callable object" << endl;
    }
};

auto main() -> int {
    thread th1(foo, 3);
    thread th2(thread_obj(), 3);

    auto f = [](int x) -> void {
        for (size_t i = 0; i < x; ++i)
            cout << "Callable lambda" << endl;
    };

    thread th3(f, 3);
    
        // Waiting for th1 finished
    th1.join();
    // Waiting for th2 finished
    th2.join();
    // Waiting for th3 finished
    th3.join();

    return 0;
}
```

Append `-pthread` to compile option.
Conveying reference to thread should use `std::ref`.

```cpp
#include <iostream>
#include <thread>

auto fun(const int &num, int &res) -> void {
    std::cout << "new thread num addr: " << &num << std::endl;
    auto i = num;
    for(; i < 10; ++i)
        std::cout << "New thread(" << std::this_thread::get_id()
                  << ") do: " << i << std::endl;
    res = i;
}

auto main() -> int {
    std::thread::id tid = std::this_thread::get_id();
    std::cout << "main pthread_self: " << tid << std::endl;
                    
    (tid == std::this_thread::get_id())
        ? std::cout << "The two thread are equal." << std::endl         
        : std::cout << "The two thread are not equal." << std::endl;
                    
    const int num = 0;
    std::cout << "main thread num addr:" << &num << std::endl;
    auto res = 0;
        
    // Convey reference to thred, using std::ref()
    std::thread th1(fun, std::ref(num), std::ref(res));

    // wait thread complete
    th1.join();

    std::cout << "main thread ends, res: " << res << std::endl;
                    
    return EXIT_SUCCESS;
}
```

If return value is neccesary, using `std::async`.

```cpp
#include <iostream>
#include <thread>
#include <future>

auto fun(const int &num) -> int {
    std::cout << "new thread num addr: " << &num << std::endl;
    auto i = num;
    for(; i < 10; ++i)
        std::cout << "New thread(" << std::this_thread::get_id()            
                  << ") do: " << i << std::endl;
    return i;
}

auto main() -> int {
    std::thread::id tid = std::this_thread::get_id();
    std::cout << "main pthread_self: " << tid << std::endl;

    (tid == std::this_thread::get_id())
        ? std::cout << "The two thread are equal." << std::endl
        : std::cout << "The two thread are not equal." << std::endl;

    const int num = 0;
    std::cout << "main thread num addr:" << &num << std::endl;
    // Convey reference to thred, using std::ref()
    std::future<int> ret = std::async(fun, std::ref(num));

    // wait thread complete
    auto res = ret.get();

    std::cout << "main thread ends, res: " << res << std::endl;

    return EXIT_SUCCESS;
}
```

Thread after detached, still depends on its parent process, but its resource will collect by OS, other than process. Detaching means it would not be suspended.

## Thread communication

### `std::mutex`

mutex is for synchronously and mutual-exclusively accessing variable.

### 死锁

Two or more processes / threads race the same resource, due to loop waiting.

```cpp
#include <iostream>
#include <thread>
#include <mutex>
#include <unistd.h>

auto printA(std::mutex &mtx1, std::mutex &mtx2) -> void {
    mtx1.lock();
    std::cout << "A eating apple..." << std::endl;
    sleep(3);
    std::cout << "A wants pear..." << std::endl;
    mtx2.lock();
    std::cout << "A eating pear..." << std::endl;
    mtx1.unlock();
    mtx2.unlock();
}

auto printB(std::mutex &mtx1, std::mutex &mtx2) -> void {
    mtx2.lock();
    std::cout << "B eating pear..." << std::endl;
    sleep(3);
    std::cout << "B wants apple..." << std::endl;
    mtx1.lock();
    std::cout << "B eating apple..." << std::endl;
    mtx2.unlock();
    mtx1.unlock();
}

auto main() -> int {
    std::mutex apple, pear;

    std::thread th1(printA, std::ref(apple), std::ref(pear));
    std::thread th2(printB, std::ref(apple), std::ref(pear));

    th1.join();
    th2.join();
    std::cout << std::endl;

    return EXIT_SUCCESS;
}
```

### 读写锁 (rwlock)

From C++17, I can use `std::shared_mutex` to archive wrlock. Before that, I can use boost rwlock API.

```cpp
#include <iostream>
#include <thread>
#include <mutex>
#include <shared_mutex>
#include <vector>

#include <unistd.h>

class ThreadSafeCounter {
public:
    ThreadSafeCounter() = default;

    auto get() const -> unsigned int {
        std::shared_lock lock(mtx);
        return value;
    }

    auto increment() -> unsigned int {
        std::unique_lock lock(mtx);
        sleep(3);
        return ++value;
    }

    auto reset() -> void {
        std::unique_lock lock(mtx);
        value = 0;
    }

private:
    mutable std::shared_mutex mtx;
    unsigned int value = 0;
};

auto main() -> int {
    ThreadSafeCounter counter;

    auto incrementAndPrint = [&counter]() {
        for (std::size_t i = 0; i < 3; ++i)
            std::cout << std::this_thread::get_id() << " "
                << counter.increment() << std::endl;
    };

    std::vector<std::thread> thread_pool;
    for (std::size_t i = 0; i < 8; ++i)
        thread_pool.push_back(std::thread(incrementAndPrint));

    for(auto th = thread_pool.begin(); th != thread_pool.end(); ++th)
        th->join();

    return EXIT_SUCCESS;
}
```

### 条件变量 (condition_variable)

Unlike mutex, `condition_variable` is used to suspend thread, until some special moments, instead of locking it. `condition_variable` is not lock, but it is often used with mutex.
`condition_variable` owns two action:

- `wait`
- `notify`

```cpp
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <condition_variable>

#include <unistd.h>

std::mutex mtx;
std::condition_variable cv;
bool ready = false;

auto printID(int id) -> void {
    std::unique_lock<std::mutex> lck(mtx);
    // wait can wait for a lock
    // wait_for can wait for a lock for time out
    // wait_until likes wait_for
    while (!ready) { cv.wait(lck); }

    std::cout << "thread " << id << std::endl;
}

auto go() -> void {
    std::unique_lock<std::mutex> lck(mtx);
    ready = true;
    cv.notify_all();
}

auto main() -> int {
    std::vector<std::thread> thread_pool;
    // Spawn 10 threads
    for (int i = 0; i < 10; ++i)
        thread_pool.push_back(std::thread(printID, i));

    // All threads were suspended to wait to be notified.
    std::cout << "10 threads start to race..." << std::endl;
    go();

    // Wait all threads complete.
    for (auto &th : thread_pool) { th.join(); }

    return EXIT_SUCCESS;
}
```

### **Reentrant Function**

**Reentrant Function** depends on nothing (includes `static`), but its own stack variables. Unrerntrant function satisfies following conditions:

- depends on global or static variables.
- used `malloc` or `free` function.
- uses stdio function.

For **unrerntrant function** should consider using mutually exclusive methods.

### Consumer and producer

### Phylosophers' dinner










