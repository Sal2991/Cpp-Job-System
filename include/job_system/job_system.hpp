#pragma once

#include <condition_variable>
#include <cstddef>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

namespace job_system {

class JobSystem {
public:
    explicit JobSystem(std::size_t workerCount = 1);
    ~JobSystem();

    JobSystem(const JobSystem&) = delete;
    JobSystem& operator=(const JobSystem&) = delete;

    void submit(std::function<void()> job);

private:
    void workerLoop();

    std::vector<std::thread> workers;
    std::queue<std::function<void()>> jobs;
    std::mutex jobsMutex;
    std::condition_variable jobsReady;
    bool stopping = false;
};

} // namespace job_system
