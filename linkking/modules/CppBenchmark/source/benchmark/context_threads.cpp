
#include "benchmark/context_threads.h"

namespace CppBenchmark {

std::string ContextThreads::description() const
{
    if ((_x < 0) && (_y < 0) && (_z < 0))
        return "(threads:" + std::to_string(_threads) + ")";
    else if ((_y < 0) && (_z < 0))
        return "(threads:" + std::to_string(_threads) + "," + std::to_string(_x) + ")";
    else if ((_z < 0))
        return "(threads:" + std::to_string(_threads) + "," + std::to_string(_x) + "," + std::to_string(_y) + ")";
    else
        return "(threads:" + std::to_string(_threads) + "," + std::to_string(_x) + "," + std::to_string(_y) + "," + std::to_string(_z) + ")";
}

} // namespace CppBenchmark
