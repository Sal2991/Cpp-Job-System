#include "job_system/job_system.hpp"

#include <atomic>
#include <cassert>
#include <future>

int main() {
    job_system::JobSystem jobs(2);
    std::atomic<int> finishedCount{0};
    std::promise<void> allDone;
    std::future<void> result = allDone.get_future();

    for (int i = 0; i < 10; ++i) {
        jobs.submit([&finishedCount, &allDone] {
            int previousCount = finishedCount.fetch_add(1);

            if (previousCount == 9) {
                allDone.set_value();
            }
        });
    }

    result.wait();
    assert(finishedCount.load() == 10);

    return 0;
}
