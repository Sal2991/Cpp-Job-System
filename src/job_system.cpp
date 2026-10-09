#include "job_system/job_system.hpp"

#include <stdexcept>
#include <utility>

namespace job_system {

JobSystem::JobSystem(std::size_t workerCount) {
    if (workerCount == 0) {
        workerCount = 1;
    }

    for (std::size_t i = 0; i < workerCount; ++i) {
        workers.emplace_back(&JobSystem::workerLoop, this);
    }
}

JobSystem::~JobSystem() {
    {
        std::lock_guard<std::mutex> lock(jobsMutex);
        stopping = true;
    }

    jobsReady.notify_all();

    for (std::thread& worker : workers) {
        if (worker.joinable()) {
            worker.join();
        }
    }
}

void JobSystem::submit(std::function<void()> job) {
    if (!job) {
        throw std::invalid_argument("job cannot be empty");
    }

    {
        std::lock_guard<std::mutex> lock(jobsMutex);

        if (stopping) {
            throw std::runtime_error("cannot submit a job while stopping");
        }

        jobs.push(std::move(job));
    }

    jobsReady.notify_one();
}

void JobSystem::workerLoop() {
    while (true) {
        std::function<void()> job;

        {
            std::unique_lock<std::mutex> lock(jobsMutex);
            jobsReady.wait(lock, [this] {
                return stopping || !jobs.empty();
            });

            if (stopping && jobs.empty()) {
                return;
            }

            job = std::move(jobs.front());
            jobs.pop();
        }

        // Run the job without holding the queue lock.
        job();
    }
}

} // namespace job_system
