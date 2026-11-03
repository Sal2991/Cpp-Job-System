#include "job_system/job_system.hpp"

#include <atomic>
#include <cassert>
#include <functional>
#include <stdexcept>

int main() {
    job_system::JobSystem jobs(2);
    std::atomic<int> finishedCount{0};

    for (int i = 0; i < 10; ++i) {
        jobs.submit([&finishedCount] {
            finishedCount.fetch_add(1);
        });
    }

    jobs.waitIdle();
    assert(finishedCount.load() == 10);
    assert(jobs.getFailedJobCount() == 0);

    // A throwing task is counted, but must not kill the worker.
    jobs.submit([] {
        throw std::runtime_error("expected test failure");
    });
    jobs.submit([&finishedCount] {
        finishedCount.fetch_add(1);
    });
    jobs.waitIdle();

    assert(jobs.getFailedJobCount() == 1);
    assert(finishedCount.load() == 11);

    bool rejectedEmptyJob = false;
    try {
        jobs.submit(std::function<void()>{});
    } catch (const std::invalid_argument&) {
        rejectedEmptyJob = true;
    }
    assert(rejectedEmptyJob);

    // A zero-worker request is normalized to one worker and still completes work.
    job_system::JobSystem singleWorker(0);
    singleWorker.submit([&finishedCount] {
        finishedCount.fetch_add(1);
    });
    singleWorker.waitIdle();
    assert(finishedCount.load() == 12);

    return 0;
}
