# C++ Job System

A small C++23 thread-pool/job-system project for learning concurrent task execution with the standard library.

## Current functionality

- Starts a fixed set of worker threads (a requested count of zero is normalized to one)
- Stores submitted `std::function<void()>` jobs in a shared queue
- Protects queue access with a mutex and wakes workers with a condition variable
- Runs jobs outside the queue lock
- Drains queued work during shutdown and joins worker threads
- Includes a multi-task example and a basic test that submits ten jobs and waits for completion

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

This is an early learning project, not a production-ready executor. Jobs currently have no return-value API or defined exception-handling policy; an exception escaping a job can terminate the process. The current test is a basic concurrency smoke test, not exhaustive coverage of shutdown races or invalid submissions.

Possible next steps include adding explicit exception handling, stronger tests, and benchmarking worker counts. Bounded retry is not implemented.
