/*
 * Question 3
 * Implement thread safe high performant queue (Single Producer, Multiple consumer) to hold quotes.
 *
 * The primary objective is to showcase your understanding of thread-safety.
 * 
 */
#pragma once

/*
 * Question 3
 * Implement thread safe high performant queue (Single Producer, Multiple consumer) to hold quotes.
 *
 * The primary objective is to showcase your understanding of thread-safety.
 *
 */
#include <vector>
#include <atomic>
#include <thread>
#include <string>
#include <iostream>
#include <array>
#include <syncstream>
#include <span>

const size_t cacheLineSize = std::hardware_constructive_interference_size;

struct alignas(cacheLineSize) Quote {
	// Adjust DataStruct if required.
	std::array<char, 28> Timestamp{0};
	double Price = 0.0;
	double Quantity = 0.0;

	Quote() = default;

	Quote(const char timestamp[28], double p, double q) : Price(p), Quantity(q)
	{
		memcpy(&Timestamp, timestamp, 28);
	}

	Quote(Quote&&) = default;
	Quote& operator =(Quote&&) = default;
	Quote(const Quote&) = delete;
	Quote& operator =(const Quote&) = delete;

	friend std::osyncstream& operator<<(std::osyncstream& os, const Quote& quote) {
		os << "Timestamp: " << quote.Timestamp.data() << ", Price = " << quote.Price << ", Quantity = " << quote.Quantity << '\n';
		return os;
	}

private:

};


template<typename T>
class QuoteQueue final {
public:
	QuoteQueue(std::size_t num_elems) :
		_store(num_elems) /* pre-allocation of vector storage. */ {
		//wait_if_empty_flag.clear();
	}

	void enqueue(T&& item)
	{
		long val = _nextWriteIndex.load(std::memory_order_acquire);
		long nxtVal = (val + 1) % _store.size();

		while (!_nextWriteIndex.compare_exchange_strong(val, nxtVal, std::memory_order_acq_rel, std::memory_order_relaxed))
		{
			val = _nextWriteIndex.load(std::memory_order_acquire);
			nxtVal = (val + 1) % _store.size();
		}
		_numElements.fetch_add(1, std::memory_order_release);
		new (&_store[nxtVal]) T(std::forward<T>(item));

		//wait_if_empty_flag.clear();
		//wait_if_empty_flag.notify_all();
	}

	T dequeue()
	{
		if (!waitUntilQueueIsEmpty())
			return T();
		
		long val = _nextReadIndex.load(std::memory_order_acquire);
		long nxtVal = (val + 1) % _store.size();

		while (!_nextReadIndex.compare_exchange_strong(val, nxtVal, std::memory_order_acq_rel, std::memory_order_relaxed))
		{
			if (!waitUntilQueueIsEmpty())
				return T();

			val = _nextReadIndex.load(std::memory_order_acquire);
			nxtVal = (val + 1) % _store.size();
		}

		_numElements.fetch_sub(1, std::memory_order_release);

		return std::move(_store[nxtVal]);
	}

	inline auto Size() const noexcept {
		return _numElements.load(std::memory_order_acquire);
	}

	inline auto IsEmpty() const noexcept {
		return _numElements.load(std::memory_order_acquire) == 0;
	}

	inline auto IsFull() const noexcept {
		return _numElements.load(std::memory_order_acquire) == _store.size();
	}

	void* operator new(size_t i)
	{
		return _mm_malloc(i, cacheLineSize);
	}

	void operator delete(void* p)
	{
		_mm_free(p);
	}

	void Done() { _done.store(true); /*wait_if_empty_flag.clear();  wait_if_empty_flag.notify_all(); */}
	
	/// Deleted default, copy & move constructors and assignment-operators.
	QuoteQueue() = delete;

	QuoteQueue(const QuoteQueue&) = delete;

	QuoteQueue(const QuoteQueue&&) = delete;

	QuoteQueue& operator=(const QuoteQueue&) = delete;

	QuoteQueue& operator=(const QuoteQueue&&) = delete;

private:

	inline bool waitUntilQueueIsEmpty()
	{
		// empty and no more producing then exit
		if (IsEmpty())
		{
			if (_done.load(std::memory_order_acquire))
				return false;

			// empty but not done yet then wait
			//std::cout << "thread is sleeping" << IsEmpty() << std::endl;
			//wait_if_empty_flag.test_and_set();
			//wait_if_empty_flag.wait(true);

			//int count = 0;
			//while (IsEmpty())
			//{
			//	if (++count == 10)
			//	{
			//		std::cout << "thread is sleeping" << IsEmpty() << std::endl;
			//		std::this_thread::sleep_for(std::chrono::nanoseconds(10));
			//		count = 0;
			//	}
			//}

			return true;
		}
		// Not done and not emptys
		return true;
	}

	/// Underlying container of data accessed in FIFO order.
	std::vector<T> _store;

	/// Atomic trackers for next index to write new data to and read new data from.
	alignas(cacheLineSize) std::atomic<long> _nextWriteIndex { -1 };
	alignas(cacheLineSize) std::atomic<long> _nextReadIndex { -1 };
	alignas(cacheLineSize) std::atomic<long> _numElements { 0 };
	//alignas(cacheLineSize) std::atomic_flag wait_if_empty_flag;
	alignas(cacheLineSize) std::atomic_bool _done{false};
};

int main() {

	std::vector<std::thread > deqThreads;
	QuoteQueue<Quote> queue(100);
	
	std::atomic_flag isProducerFinished;
	isProducerFinished.clear();
	std::thread enqThread([&] {
		int count = 1;
		while (count <= 100) {
			Quote quote("2024-02-12 13:12:13:567.788", 100. + count, 50. + count * 0.5 );
			queue.enqueue(std::move(quote));
			++count;
		}
		queue.Done();
		isProducerFinished.test_and_set();
	});


	for (int i = 0; i < 10; ++i) {
		deqThreads.emplace_back([&] {
			// std::osyncstream needs the sync mechanism, it is not thread safe, it just another buffer which holds the 
			// data until destructor is called and moves it to std::cout
			std::osyncstream synced_cout_stream(std::cout);
			while (!isProducerFinished.test(std::memory_order_acquire) || !queue.IsEmpty()) {
				const auto& quote = queue.dequeue(); // dequeue should block if queue is empty
				synced_cout_stream << quote << '\n';
			}
			std::cout << "consumer thread done" << std::endl;
			});
	}

	// Your code goes here.
	// Wait for enqueue, dequeue threads to finisih
	if (enqThread.joinable())
		enqThread.join();

	for (int i = 0; i < 10; ++i) {
		if (deqThreads[i].joinable())
			deqThreads[i].join();
	}


	return 0;
}