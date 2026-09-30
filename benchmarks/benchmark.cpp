//
// Created by deakin on 9/28/26.
//

#include <forward_list>
#include <benchmark/benchmark.h>
#include "LinkedList.hpp"

static void BM_PUSH_BACK(benchmark::State& state)
{
    for (auto _ : state)
    {
        ThreadSafeList::ThreadSafeList<int> l {};

        for (auto i {0}; i < state.range(0); ++i)
        {
            l.push_back(0);
        }
    }
}

static void BASELINE_PUSH_FRONT(benchmark::State& state)
{
    for (auto _ : state)
    {
        std::pmr::forward_list<int> l;

        for (auto i {0}; i < state.range(0); ++i)
        {
            l.push_front(0);
        }
    }
}

static void BM_PUSH_FRONT(benchmark::State& state)
{
    for (auto _ : state)
    {
        ThreadSafeList::ThreadSafeList<int> l {};

        for (auto i {0}; i < state.range(0); ++i)
        {
            l.push_front(0);
        }
    }
}

// test different benchmark ranges
BENCHMARK(BM_PUSH_BACK)
  -> Arg(10)
  -> Arg(100)
  -> Arg(1000)
  -> Arg(10000);

BENCHMARK(BASELINE_PUSH_FRONT)
  -> Arg(10)
  -> Arg(100)
  -> Arg(1000)
  -> Arg(10000)
  -> Arg(100000)
  -> Arg(1000000);

BENCHMARK(BM_PUSH_FRONT)
  -> Arg(10)
  -> Arg(100)
  -> Arg(1000)
  -> Arg(10000)
  -> Arg(100000)
  -> Arg(1000000);



BENCHMARK_MAIN();
