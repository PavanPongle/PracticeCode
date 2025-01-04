#pragma once

#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <atomic>
#include <boost/config.hpp>

#ifndef _WIN32

#include <unistd.h>
#include <sys/syscall.h>

#else

#include <processthreadsapi.h>
#include <winbase.h>
#include <Windows.h>
#endif



unsigned int GetNextCoreForThreadAffinity()
{
	static auto total_threads = std::thread::hardware_concurrency();
	static unsigned int current_core = 0;
	current_core = (current_core + 1) % total_threads;
	return current_core;
}


#ifdef _WIN32

/// Set affinity for current thread to be pinned to the provided core_id.
inline auto setThreadCore(int core_id) noexcept {

	DWORD_PTR dw = SetThreadAffinityMask(::GetCurrentThread(), DWORD_PTR(1) << core_id);
	if (BOOST_UNLIKELY(dw == 0))
	{
		DWORD dwErr = GetLastError();
		std::cerr << "SetThreadAffinityMask failed, GLE=" << dwErr << '\n';
	}
}

#else

/// Set affinity for current thread to be pinned to the provided core_id.
inline auto setThreadCore(int core_id) noexcept {
	cpu_set_t cpuset;

	CPU_ZERO(&cpuset);
	CPU_SET(core_id, &cpuset);

	return (pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset) == 0);
}

#endif // _WIN32