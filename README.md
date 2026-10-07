# C++ Job System

A C++ job system that I'm building to learn more about threads and running tasks at the same time.

I'm working on this step by step to get more comfortable with **multithreading, synchronization, task scheduling, and C++**.

## Goals

- Learn how thread pools work
- Practice using threads and the C++ standard library
- Make a way to submit tasks to worker threads
- Add tests and benchmarks as I build more
- See how changing the number of worker threads affects performance

## Planned Roadmap

- [ ] Basic worker pool
- [ ] Thread-safe job queue
- [ ] Clean worker shutdown
- [ ] Task submission API
- [ ] Futures / task results
- [ ] Tests
- [ ] Benchmarks
- [ ] Task priorities
- [ ] Work stealing (maybe later)

## Project Structure

```text
include/      Public headers
src/          Implementation
examples/     Small usage examples
tests/        Automated tests
benchmarks/   Performance benchmarks
```

## Requirements

- C++23 compiler
- CMake 3.20+
- Standard C++ library

## Build

```bash
cmake -S . -B build
cmake --build build
```

I'm still building this project, so some of the parts above are planned and not finished yet.

## License

MIT
