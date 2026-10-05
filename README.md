# C++ Job System

A from-scratch C++ job system for executing CPU-bound tasks across a configurable pool of worker threads.

This project is being built incrementally to explore **multithreading, synchronization, task scheduling, and performance** in modern C++.

## Goals

- Build a reusable thread pool / job system from scratch
- Learn thread synchronization with the C++ standard library
- Support safe task submission and worker shutdown
- Add tests and performance benchmarks
- Investigate how different worker counts affect throughput

## Planned Roadmap

- [ ] Basic worker pool
- [ ] Thread-safe job queue
- [ ] Clean worker shutdown
- [ ] Task submission API
- [ ] Futures / task results
- [ ] Tests
- [ ] Benchmarks
- [ ] Task priorities
- [ ] Work stealing (advanced)

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
- CMake 4.2+
- Standard C++ library

## Build

```bash
cmake -S . -B build
cmake --build build
```

The implementation is intentionally being developed step by step rather than starting with a finished thread pool.

## License

MIT
