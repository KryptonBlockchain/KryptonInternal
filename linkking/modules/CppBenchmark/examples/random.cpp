

#include "benchmark/cppbenchmark.h"

BENCHMARK("rand()")
{
    rand();
}

BENCHMARK("rand()-till-zero", Settings().Infinite().Attempts(10))
{
    if (rand() == 0)
        context.Cancel();
}

BENCHMARK_MAIN()
