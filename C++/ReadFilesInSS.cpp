// ReadFilesInSS.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <benchmark/benchmark.h>
#include <thread>
#include <future>
#include <string>
#include <array>
#include <fstream>
#include <sstream>
#include <memory>
#include <vector>

namespace bm = benchmark;

std::array<std::string, 3> files{
    "D:/vcpkg/CONTRIBUTING.md",
    "D:/vcpkg/CONTRIBUTING_pt.md",
    "D:/vcpkg/CONTRIBUTING_zh.md"
    //"D:/1.txt",
    //"D:/2.txt",
    //"D:/3.txt"
};

std::vector<std::ifstream> fstreams;

void Init()
{
    std::cout << "thread Id: " << std::this_thread::get_id() << std::endl;

    for (auto& file : files)
    {
        fstreams.emplace_back(std::ifstream());

        fstreams.rbegin()->open(file);

        if (fstreams.rbegin()->is_open() == false)
        {
            std::cout << "error in file open " << file;
            continue;
        }
    }
}

static void DoSetup(const benchmark::State& state) {
    Init();
}

static void DoTeardown(const benchmark::State& state) {

    fstreams.clear();
}

void ReadFiles()
{
    std::stringstream ss;
    for (auto& ifstr : fstreams)
    {
        ss << ifstr.rdbuf();
    }

    bm::DoNotOptimize(std::cout << ss.str().length() << std::endl);
}

void ReadFiles2()
{
    std::cout << "thread Id: " << std::this_thread::get_id() << std::endl;

    size_t total_size = 0;
    std::vector<size_t> content_length((fstreams).size());

    for (short index = 0; index < (fstreams).size(); ++index)
    {
        fstreams[index].seekg(0, std::ios::end);    // go to the end
        content_length[index] = ((fstreams)[index].tellg());
        total_size += content_length[index];
        
        (fstreams)[index].seekg(0);
    }

    std::string str(total_size + 1, '\0');

    size_t location = 0;
    for (short index = 0; index < (fstreams).size() ; ++index)
    {
        (fstreams)[index].read(&str[location], content_length[index]);
        location += content_length[index];

        if (!(fstreams)[index].good())
        {
            std::cout << "error in reading file" << std::endl;
        }
    }

    bm::DoNotOptimize(std::cout << total_size << std::endl);
}

void Benchmark1(bm::State& state)
{
    for (auto _ : state)
        ReadFiles();
}

void Benchmark2(bm::State& state)
{
    for (auto _ : state)
        ReadFiles2();
}

BENCHMARK(Benchmark1)->Setup(DoSetup)->Teardown(DoTeardown)->Iterations(1);

BENCHMARK(Benchmark2)->Setup(DoSetup)->Teardown(DoTeardown)->Iterations(1);