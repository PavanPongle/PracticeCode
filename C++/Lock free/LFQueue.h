#pragma once

#include <string>
#include <atomic>
#include <vector>
#include <thread>

template<typename T>
class LFQueue final {
public:
    LFQueue(std::size_t num_elems) :
        _store(num_elems) /* pre-allocation of vector storage. */ {
    }

    inline auto getNextToWriteTo() noexcept {
        return &_store[_nextWriteIndex.load(std::memory_order_relaxed)];
    }

    inline auto updateWriteIndex() noexcept {
        auto val = _nextWriteIndex.load(std::memory_order_acquire);
        _nextWriteIndex.store((val + 1) % _store.size());
        _numElements.fetch_add(1, std::memory_order_release);
    }

    inline auto getNextToRead() const noexcept -> const T* {
        return (Size() ? &_store[_nextReadIndex] : nullptr);
    }

    inline auto updateReadIndex() noexcept {
        auto val = _nextReadIndex.load(std::memory_order_acquire);
        _nextReadIndex.store((val + 1) % _store.size()); // wrap around at the end of container size.
        _numElements.fetch_sub(1, std::memory_order_release);
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
        return _mm_malloc(i, 64);
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
    alignas(64) std::atomic<size_t> _nextWriteIndex = { 0 };
    //size_t _padding1[7];
    alignas(64) std::atomic<size_t> _nextReadIndex = { 0 };
    //size_t _padding2[7];
    alignas(64) std::atomic<size_t> _numElements = { 0 };
};