cmake_minimum_required(VERSION 3.20)

project(cpp_job_system VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(job_system src/job_system.cpp)
target_include_directories(job_system PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(job_system_example examples/basic.cpp)
target_link_libraries(job_system_example PRIVATE job_system)

enable_testing()
add_executable(job_system_tests tests/test_job_system.cpp)
target_link_libraries(job_system_tests PRIVATE job_system)
add_test(NAME job_system_tests COMMAND job_system_tests)
