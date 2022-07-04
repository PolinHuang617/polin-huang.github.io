#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <queue>
#include <cmath>
#include <thread>
#include <utility>
#include <numeric>
#include <algorithm>
#include <functional>
#include <mutex>
#include <boost/progress.hpp>

// template <typename T, std::function<T(std::vector<T>)>, std::vector<T>>
template <typename T>
class Queue {
public:
    explicit Queue() {
        m_queue = std::priority_queue
        <
            std::map
            <
                std::function<T(std::vector<T>)>,
                std::vector<T>
            >
        >();
    }

    T begin() const {
        std::lock_guard<std::mutex> locker(m_mtx);
        return m_queue.top();
    }

    void push(std::function<T(std::vector<T>)> func, std::vector<T> data) {
        std::lock_guard<std::mutex> locker(m_mtx);
        m_queue.push({ func, data });
    }

    std::map<std::function<T(std::vector<T>)>, std::vector<T>> pop() {
        std::lock_guard<std::mutex> locker(m_mtx);
        return m_queue.pop();
    }

    std::size_t size() const {
        std::lock_guard<std::mutex> locker(m_mtx);
        return m_queue.size();
    }

    bool isEmpty() const {
        std::lock_guard<std::mutex> locker(m_mtx);
        return m_queue.empty();
    }

private:
    std::priority_queue
    <
        std::map
        <
            std::function<T(std::vector<T>)>,
            std::vector<T>
        >
    > m_queue;
    std::mutex m_mtx;
};

template <typename T>
class ThreadPool {
public:
    explicit ThreadPool(size_t workerNumber = 1) : m_workerNumber(workerNumber) {
        for (size_t i = 0; i < workerNumber; ++i) {
            m_workers.emplace(m_workers.end(), Worker());
        }
    }

    std::thread::id exec(std::function<T(std::vector<T>)> func, std::vector<T> container)
    {
        for (const auto& worker : m_workers)
        {
            if (worker.status() == IDLE)
            {
                worker.load(func, container);
                return worker.id();
            }
        }
        // No worker idle currently, return main thread id.
        return std::this_thread::id();
    }

    inline T get(const std::thread::id& id) { return m_workers[id].getResult(); }

private:
    enum WORK_STATUS { IDLE, BUSY, DONE };

    class Worker {
    public:
        Worker() {
            m_status = IDLE;
            m_th = std::thread([&]() {
                std::cout << __func__ << " Thread id: " << std::this_thread::get_id() << std::endl;
                while (true) {
                    if (m_queue.size() > 0) {
                        std::cout << "Queue has data!" << std::endl;
                        m_data = m_queue.pop();

                        m_status = BUSY;
                    }
                    m_status = IDLE;
                }
            });
        }

        inline WORK_STATUS status() const { return m_status; }

        inline std::thread::id id() const { return m_th.get_id(); }

        inline std::thread::id load(std::function<T(std::vector<T>)> func, std::vector<T> data)
        {
            m_queue.push(func, data);
            return std::this_thread::get_id();
        }

        inline T getResult()
        {
            while (m_status != DONE) { return m_result; }
        }

    private:
        std::thread m_th;
        WORK_STATUS m_status;
        std::vector<T> m_data;
        T m_result;
    };

private:
    std::vector<Worker> m_workers;
    size_t m_workerNumber;
    static Queue<T> m_queue;
    // static Queue<T, std::function<T(std::vector<T>)>, std::vector<T>> m_queue;
};

template <typename T>
Queue<T> ThreadPool<T>::m_queue;

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

// Task manager
template <typename Iterator, typename T>
T parallelAccum(Iterator first, Iterator last, T &container, void(*callBack)(Iterator, Iterator, T&)) {
    // Count elements in container
    const std::size_t size = std::distance(first, last);
    if (!size) { return container; }

    // Acquire paralleled threads number that hardware supported.
    // For avoiding high CPU occupation, 60% threads number is better.
    const std::size_t numThread = 4; //std::thread::hardware_concurrency() * 0.6;
    // Actual element block per thread.
    const std::size_t blockSize = size / numThread;

    // Save process results per thread, default size is 1,
    // which only main thread run.
    std::vector<T> results(1);
    std::vector<std::thread> threads;

    // Start paralleling run
    Iterator blockBegin = first;
    if (size > numThread) {
        results.resize(numThread);
        // Spawn numThread - 1 threads, because main thread is a thread.
        threads.resize(numThread - 1);
        for (std::size_t i = 0; i < (numThread - 1); ++i) {
            Iterator blockEnd = blockBegin;
            // Push iterator a block forward.
            std::advance(blockEnd, blockSize);
            // Pass reference of each block address, 
            // to garrentee file original sequence.
            threads[i] = std::thread(callBack, blockBegin, blockEnd, std::ref(results[i]));
            blockBegin = blockEnd;
        }
        // main thread process the last block
        callBack(blockBegin, last, std::ref(results[numThread - 1]));

        // Wait all thread ends.
        std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));
    }
    else {
        callBack(blockBegin, last, std::ref(results[0]));
    }

    return std::accumulate(results.begin(), results.end(), container);
}

auto main() -> int {
    std::vector<int> vI;
    for (std::size_t i = 1; i < 5010000; ++i) {
        vI.push_back(i);
    }

    /*
    {
        int sum = 0;
        boost::progress_timer pt;
        sum = parallelAccum(vI.cbegin(), vI.cend(), sum, accum);
        std::cout << "1. sum: " << sum << ", time spent: ";
    }

    {
        int sum = 0;
        boost::progress_timer pt;
        accum(vI.begin(), vI.end(), sum);
        std::cout << "2. sum: " << sum << ", time spent: ";
    }
    */
    // ThreadPool<int> pool(4);
    // pool.get();

    return EXIT_SUCCESS;
}


