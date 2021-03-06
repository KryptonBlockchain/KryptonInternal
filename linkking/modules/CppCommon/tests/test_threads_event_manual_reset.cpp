
#include "test.h"

#include "threads/event_manual_reset.h"
#include "threads/thread.h"

#include <atomic>
#include <thread>

using namespace CppCommon;

TEST_CASE("Manual-reset event", "[CppCommon][Threads]")
{
    int concurrency = 8;
    std::atomic<int> count(0);

    EventManualReset event;

    // Start some threads
    std::vector<std::thread> threads;
    for (int thread = 0; thread < concurrency; ++thread)
    {
        threads.emplace_back([&event, &count, thread]()
        {
            // Sleep for a while...
            Thread::Sleep(thread * 10);

            // Wait for the event
            event.Wait();

            // Increment threads counter
            ++count;
        });
    }

    // Allow threads to start
    Thread::Sleep(100);

    // Signal the event
    event.Signal();

    // Wait for all threads to complete
    for (auto& thread : threads)
        thread.join();

    // Check results
    REQUIRE(count == concurrency);
}
