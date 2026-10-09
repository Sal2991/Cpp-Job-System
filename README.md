# C++ Job System

I'm building a small C++ job system to learn how threads can run tasks at the same time.

## What works so far

- Starts a fixed number of worker threads
- Adds jobs to a queue that workers share safely
- Wakes a worker when a new job is submitted
- Waits for queued jobs to finish when the job system shuts down
- Includes a small example and a basic test for running multiple jobs

## Still to do

- Decide how exceptions thrown by jobs should be handled
- Add a way to get return values from jobs
- Add more tests for shutdown and invalid submissions
- Benchmark different worker counts
- Try the project on more than one compiler

This is still an early version. The queue and worker loop are the first part, not a complete production job system.
