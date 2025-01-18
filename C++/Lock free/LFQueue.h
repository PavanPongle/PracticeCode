#pragma once

#include <string>
#include <atomic>
#include <vector>
#include <thread>

const size_t cacheLineSize = std::hardware_constructive_interference_size;

template<typename T>
class LFQueue final {
public:
    LFQueue(std::size_t num_elems) :
        _store(num_elems) /* pre-allocation of vector storage. */ {
    }

    T* GetNextToWrite()
    {
        size_t val = _back.load(std::memory_order_acquire);
        size_t nxtVal = (val + 1 ) % _size;

        while (!_back.compare_exchange_strong(val, nxtVal, std::memory_order_acq_rel, std::memory_order_relaxed))
        {
            val = _back.load(std::memory_order_acquire);
            nxtVal = (val + 1) % _size;
        }
        _used.fetch_add(1, std::memory_order_release);
        return &_buff[nxtVal];
    }

    T* GetNextToRead()
    {
        size_t val = _front.load(std::memory_order_acquire);
        size_t nxtVal = (val + 1) % _size;

        while (!_front.compare_exchange_strong(val, nxtVal, std::memory_order_acq_rel, std::memory_order_relaxed))
        {
            val = _front.load(std::memory_order_acquire);
            nxtVal = (val + 1) % _size;
        }
        _used.fetch_sub(1, std::memory_order_release);
        return &_buff[nxtVal];
    }

    inline auto Size() const noexcept {
        return _numElements.load();
    }

    inline auto IsEmpty() const noexcept {
        return _numElements.load() == 0;
    }

    inline auto IsFull() const noexcept {
        return _numElements.load() == _store.size();
    }

    void* operator new(size_t i)
    {
        return _mm_malloc(i, cacheLineSize);
    }

    void operator delete(void* p)
    {
        _mm_free(p);
    }

    /// Deleted default, copy & move constructors and assignment-operators.
    LFQueue() = delete;

    LFQueue(const LFQueue&) = delete;

    LFQueue(const LFQueue&&) = delete;

    LFQueue& operator=(const LFQueue&) = delete;

    LFQueue& operator=(const LFQueue&&) = delete;

private:
    /// Underlying container of data accessed in FIFO order.
    std::vector<T> _store;

    /// Atomic trackers for next index to write new data to and read new data from.
    alignas(cacheLineSize) std::atomic<size_t> _nextWriteIndex = { 0 };
    //size_t _padding1[7];
    alignas(cacheLineSize) std::atomic<size_t> _nextReadIndex = { 0 };
    //size_t _padding2[7];
    alignas(cacheLineSize) std::atomic<size_t> _numElements = { 0 };
};


Buffer<size_t> g_buff(100);

void Producer()
{
    static size_t val = 0;

    while (!g_buff.IsFull())
    {
        size_t* ptr = g_buff.GetNextToWrite();

        new (ptr) size_t(val++);
    }
}


void Consumer()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    while (!g_buff.IsEmpty())
    {
        size_t* ptr = g_buff.GetNextToRead();

        std::cout << *ptr << " " ;
    }
}

int main()
{
    std::thread p(Producer);
    std::thread c(Consumer);

    p.join();
    c.join();
}

