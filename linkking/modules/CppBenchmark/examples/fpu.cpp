
#include "benchmark/cppbenchmark.h"

#include <cmath>

BENCHMARK("sin()")
{
    static double sum = 0;
    sum += sin(123.456);
}

BENCHMARK("cos()")
{
    static double sum = 0;
    sum += cos(123.456);
}

BENCHMARK("tan()")
{
    static double sum = 0;
    sum += tan(123.456);
}

BENCHMARK_MAIN()
