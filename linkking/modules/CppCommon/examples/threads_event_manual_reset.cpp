
#include "threads/event_manual_reset.h"
#include "threads/thread.h"

#include <iostream>
#include <thread>
#include <vector>

int main(int argc, char** argv)
{
    int concurrency = 8;

    CppCommon::EventManualReset event;

    // Start some threads
    std::vector<std::thread> threads;
    for (int thread = 0; thread < concurrency; ++thread)
    {
        threads.emplace_back([&event, thread]()
        {
            std::cout << "Thread " << thread << " initialized!" << std::endl;

            // Sleep for a while...
            CppCommon::Thread::SleepFor(CppCommon::Timespan::milliseconds(thread * 10));

            std::cout << "Thread " << thread << " waiting for the event!" << std::endl;

            // Wait for the event
            event.Wait();

            std::cout << "Thread " << thread << " signaled!" << std::endl;
        });
    }

    // Allow threads to start
    CppCommon::Thread::SleepFor(CppCommon::Timespan::milliseconds(100));

    // Signal the event
    std::cout << "Signal event!" << std::endl;
    event.Signal();

    // Wait for all threads
    for (auto& thread : threads)
        thread.join();

    return 0;
}
