#include "job_system/job_system.hpp"

#include <array>
#include <atomic>
#include <future>
#include <iostream>

int main() {
    job_system::JobSystem jobs(2);
    std::atomic<int> finishedCount{0};
    std::array<std::promise<void>, 5> done;
    std::array<std::future<void>, 5> results;

    for (std::size_t i = 0; i < done.size(); ++i) {
        results[i] = done[i].get_future();

        jobs.submit([i, &finishedCount, &done] {
            ++finishedCount;
            std::cout << "finished job " << i << '\n';
            done[i].set_value();
        });
    }

    for (std::future<void>& result : results) {
        result.wait();
    }

    std::cout << "jobs finished: " << finishedCount.load() << '\n';
    return 0;
}
