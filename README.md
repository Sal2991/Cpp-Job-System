# C++ Job System

A small C++23 thread-pool/job-system project for learning concurrent task execution with the standard library.

## Current functionality

- Starts a fixed set of worker threads (a requested count of zero is normalized to one)
- Stores submitted `std::function<void()>` jobs in a shared queue
- Protects queue access with a mutex and wakes workers with a condition variable
- Runs jobs outside the queue lock
- Provides `waitIdle()` to block until the queue is empty and all active jobs finish
- Drains queued work during shutdown and joins worker threads
- Rejects empty job functions with `std::invalid_argument`
- Includes an example and tests for completion tracking, empty submissions, and zero-worker normalization

## Build and test

Requirements: CMake 3.20+ and a compiler with C++23 support.

```sh
cmake -S . -B build
cmake --build build --config Release
ctest --test-dir build -C Release --output-on-failure
```

Run the example:

```sh
./build/job_system_example
```

For multi-configuration generators such as Visual Studio, the executable is typically under `build/Release` (or `build/Debug`).

## Limitations and next steps

This is an early learning project, not a production-ready executor. Jobs have no return-value API or defined exception-handling policy; an exception escaping a job can terminate the process. `waitIdle()` is intended to wait for jobs to complete, not to prevent other threads from submitting more work concurrently. The tests are useful regression checks but are not exhaustive coverage of shutdown races.

Next steps: define an exception policy, add stress tests for concurrent submission/shutdown, and benchmark worker counts.
